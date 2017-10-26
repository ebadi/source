/*

   nsjail - networking routines
   -----------------------------------------

   Copyright 2014 Google Inc. All Rights Reserved.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

*/

#include "net.h"

#include <arpa/inet.h>
#include <errno.h>
#include <net/if.h>
#include <net/route.h>
#include <netinet/in.h>
#include <netinet/ip6.h>
#include <netinet/tcp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/ioctl.h>
#include <sys/queue.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "log.h"
#include "subproc.h"

#define IFACE_NAME "vs"

extern char** environ;

#if defined(NSJAIL_NL3_WITH_MACVLAN)
#include <netlink/route/link.h>
#include <netlink/route/link/macvlan.h>
bool netInitNsFromParent(struct nsjconf_t* nsjconf, int pid)
{
	if (nsjconf->clone_newnet == false) {
		return true;
	}
	if (nsjconf->iface_vs == NULL) {
		return true;
	}

	LOG_D("Putting iface:'%s' into namespace of PID:%d (with libnl3)", nsjconf->iface_vs, pid);

	struct nl_sock* sk = nl_socket_alloc();
	if (sk == NULL) {
		LOG_E("Could not allocate socket with nl_socket_alloc()");
		return false;
	}

	int err;
	if ((err = nl_connect(sk, NETLINK_ROUTE)) < 0) {
		LOG_E("Unable to connect socket: %s", nl_geterror(err));
		nl_socket_free(sk);
		return false;
	}

	struct rtnl_link* rmv = rtnl_link_macvlan_alloc();
	if (rmv == NULL) {
		LOG_E("rtnl_link_macvlan_alloc(): %s", nl_geterror(err));
		nl_socket_free(sk);
		return false;
	}

	struct nl_cache* link_cache;
	if ((err = rtnl_link_alloc_cache(sk, AF_UNSPEC, &link_cache)) < 0) {
		LOG_E("rtnl_link_alloc_cache(): %s", nl_geterror(err));
		rtnl_link_put(rmv);
		nl_socket_free(sk);
		return false;
	}

	int master_index = rtnl_link_name2i(link_cache, nsjconf->iface_vs);
	if (master_index == 0) {
		LOG_E("rtnl_link_name2i(): Did not find '%s' interface", nsjconf->iface_vs);
		nl_cache_free(link_cache);
		rtnl_link_put(rmv);
		nl_socket_free(sk);
		return false;
	}

	rtnl_link_set_name(rmv, IFACE_NAME);
	rtnl_link_set_link(rmv, master_index);
	rtnl_link_set_ns_pid(rmv, pid);

	if ((err = rtnl_link_add(sk, rmv, NLM_F_CREATE)) < 0) {
		LOG_E("rtnl_link_add(name:'%s' link:'%s'): %s", IFACE_NAME, nsjconf->iface_vs,
		    nl_geterror(err));
		nl_cache_free(link_cache);
		rtnl_link_put(rmv);
		nl_socket_free(sk);
		return false;
	}

	nl_cache_free(link_cache);
	rtnl_link_put(rmv);
	nl_socket_free(sk);
	return true;
}
#else // defined(NSJAIL_NL3_WITH_MACVLAN)

bool netInitNsFromParent(struct nsjconf_t* nsjconf, int pid)
{
	if (nsjconf->clone_newnet == false) {
		return true;
	}
	if (nsjconf->iface_vs == NULL) {
		return true;
	}

	LOG_D(
	    "Putting iface:'%s' into namespace of PID:%d (with /sbin/ip)", nsjconf->iface_vs, pid);

	char pid_str[256];
	snprintf(pid_str, sizeof(pid_str), "%d", pid);

	const char* argv[] = { "/sbin/ip", "link", "add", "link", (char*)nsjconf->iface_vs, "name",
		IFACE_NAME, "netns", pid_str, "type", "macvlan", "mode", "bridge", NULL };
	if (subprocSystem(argv, environ) != 0) {
		LOG_E("Couldn't create MACVTAP interface for '%s'", nsjconf->iface_vs);
		return false;
	}

	return true;
}
#endif // defined(NSJAIL_NL3_WITH_MACVLAN)

static bool netIsSocket(int fd)
{
	int optval;
	socklen_t optlen = sizeof(optval);
	int ret = getsockopt(fd, SOL_SOCKET, SO_TYPE, &optval, &optlen);
	if (ret == -1) {
		return false;
	}
	return true;
}

bool netLimitConns(struct nsjconf_t* nsjconf, int connsock)
{
	/* 0 means 'unlimited' */
	if (nsjconf->max_conns_per_ip == 0) {
		return true;
	}

	struct sockaddr_in6 addr;
	char cs_addr[64];
	netConnToText(connsock, true /* remote */, cs_addr, sizeof(cs_addr), &addr);

	unsigned int cnt = 0;
	struct pids_t* p;
	TAILQ_FOREACH(p, &nsjconf->pids, pointers)
	{
		if (memcmp(addr.sin6_addr.s6_addr, p->remote_addr.sin6_addr.s6_addr,
			sizeof(*p->remote_addr.sin6_addr.s6_addr))
		    == 0) {
			cnt++;
		}
	}

	if (cnt >= nsjconf->max_conns_per_ip) {
		LOG_W("Rejecting connection from '%s', max_conns_per_ip limit reached: %u", cs_addr,
		    nsjconf->max_conns_per_ip);
		return false;
	}

	return true;
}

int netGetRecvSocket(const char* bindhost, int port)
{
	if (port < 1 || port > 65535) {
		LOG_F("TCP port %d out of bounds (0 <= port <= 65535), specify one with --port "
		      "<port>",
		    port);
	}

	char bindaddr[128];
	snprintf(bindaddr, sizeof(bindaddr), "%s", bindhost);
	struct in_addr in4a;
	if (inet_pton(AF_INET, bindaddr, &in4a) == 1) {
		snprintf(bindaddr, sizeof(bindaddr), "::ffff:%s", bindhost);
		LOG_D("Converting bind IPv4:'%s' to IPv6:'%s'", bindhost, bindaddr);
	}

	struct in6_addr in6a;
	if (inet_pton(AF_INET6, bindaddr, &in6a) != 1) {
		PLOG_E(
		    "Couldn't convert '%s' (orig:'%s') into AF_INET6 address", bindaddr, bindhost);
		return -1;
	}

	int sockfd = socket(AF_INET6, SOCK_STREAM, 0);
	if (sockfd == -1) {
		PLOG_E("socket(AF_INET6)");
		return -1;
	}
	int so = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &so, sizeof(so)) == -1) {
		PLOG_E("setsockopt(%d, SO_REUSEADDR)", sockfd);
		return -1;
	}
	struct sockaddr_in6 addr = {
		.sin6_family = AF_INET6,
		.sin6_port = htons(port),
		.sin6_flowinfo = 0,
		.sin6_addr = in6a,
		.sin6_scope_id = 0,
	};
	if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
		close(sockfd);
		PLOG_E("bind(host:[%s] (orig:'%s'), port:%d)", bindaddr, bindhost, port);
		return -1;
	}
	if (listen(sockfd, SOMAXCONN) == -1) {
		close(sockfd);
		PLOG_E("listen(%d)", SOMAXCONN);
		return -1;
	}

	char ss_addr[64];
	netConnToText(sockfd, false /* remote */, ss_addr, sizeof(ss_addr), NULL);
	LOG_I("Listening on %s", ss_addr);

	return sockfd;
}

int netAcceptConn(int listenfd)
{
	struct sockaddr_in6 cli_addr;
	socklen_t socklen = sizeof(cli_addr);
	int connfd = accept(listenfd, (struct sockaddr*)&cli_addr, &socklen);
	if (connfd == -1) {
		if (errno != EINTR) {
			PLOG_E("accept(%d)", listenfd);
		}
		return -1;
	}

	char cs_addr[64], ss_addr[64];
	netConnToText(connfd, true /* remote */, cs_addr, sizeof(cs_addr), NULL);
	netConnToText(connfd, false /* remote */, ss_addr, sizeof(ss_addr), NULL);
	LOG_I("New connection from: %s on: %s", cs_addr, ss_addr);

	return connfd;
}

void netConnToText(int fd, bool remote, char* buf, size_t s, struct sockaddr_in6* addr_or_null)
{
	if (netIsSocket(fd) == false) {
		snprintf(buf, s, "[STANDALONE_MODE]");
		return;
	}

	struct sockaddr_in6 addr;
	socklen_t addrlen = sizeof(addr);
	if (remote) {
		if (getpeername(fd, (struct sockaddr*)&addr, &addrlen) == -1) {
			PLOG_W("getpeername(%d)", fd);
			snprintf(buf, s, "[unknown]");
			return;
		}
	} else {
		if (getsockname(fd, (struct sockaddr*)&addr, &addrlen) == -1) {
			PLOG_W("getsockname(%d)", fd);
			snprintf(buf, s, "[unknown]");
			return;
		}
	}

	if (addr_or_null) {
		memcpy(addr_or_null, &addr, sizeof(*addr_or_null));
	}

	char tmp[s];
	if (inet_ntop(AF_INET6, addr.sin6_addr.s6_addr, tmp, s) == NULL) {
		PLOG_W("inet_ntop()");
		snprintf(buf, s, "[unknown]:%hu", ntohs(addr.sin6_port));
		return;
	}
	snprintf(buf, s, "[%s]:%hu", tmp, ntohs(addr.sin6_port));
	return;
}

static bool netIfaceUp(const char* ifacename)
{
	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if (sock == -1) {
		PLOG_E("socket(AF_INET, SOCK_STREAM, IPPROTO_IP)");
		return false;
	}

	struct ifreq ifr;
	memset(&ifr, '\0', sizeof(ifr));
	snprintf(ifr.ifr_name, IF_NAMESIZE, "%s", ifacename);

	if (ioctl(sock, SIOCGIFFLAGS, &ifr) == -1) {
		PLOG_E("ioctl(iface='%s', SIOCGIFFLAGS, IFF_UP)", ifacename);
		close(sock);
		return false;
	}

	ifr.ifr_flags |= (IFF_UP | IFF_RUNNING);

	if (ioctl(sock, SIOCSIFFLAGS, &ifr) == -1) {
		PLOG_E("ioctl(iface='%s', SIOCSIFFLAGS, IFF_UP|IFF_RUNNING)", ifacename);
		close(sock);
		return false;
	}

	close(sock);
	return true;
}

static bool netConfigureVs(struct nsjconf_t* nsjconf)
{
	struct ifreq ifr;
	memset(&ifr, '\0', sizeof(ifr));
	snprintf(ifr.ifr_name, IF_NAMESIZE, "%s", IFACE_NAME);
	struct in_addr addr;

	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if (sock == -1) {
		PLOG_E("socket(AF_INET, SOCK_STREAM, IPPROTO_IP)");
		return false;
	}

	if (inet_pton(AF_INET, nsjconf->iface_vs_ip, &addr) != 1) {
		PLOG_E("Cannot convert '%s' into an IPv4 address", nsjconf->iface_vs_ip);
		close(sock);
		return false;
	}
	if (addr.s_addr == INADDR_ANY) {
		LOG_D("IPv4 address for interface '%s' not set", IFACE_NAME);
		close(sock);
		return true;
	}

	struct sockaddr_in* sa = (struct sockaddr_in*)(&ifr.ifr_addr);
	sa->sin_family = AF_INET;
	sa->sin_addr = addr;
	if (ioctl(sock, SIOCSIFADDR, &ifr) == -1) {
		PLOG_E("ioctl(iface='%s', SIOCSIFADDR, '%s')", IFACE_NAME, nsjconf->iface_vs_ip);
		close(sock);
		return false;
	}

	if (inet_pton(AF_INET, nsjconf->iface_vs_nm, &addr) != 1) {
		PLOG_E("Cannot convert '%s' into a IPv4 netmask", nsjconf->iface_vs_nm);
		close(sock);
		return false;
	}
	sa->sin_family = AF_INET;
	sa->sin_addr = addr;
	if (ioctl(sock, SIOCSIFNETMASK, &ifr) == -1) {
		PLOG_E("ioctl(iface='%s', SIOCSIFNETMASK, '%s')", IFACE_NAME, nsjconf->iface_vs_nm);
		close(sock);
		return false;
	}

	if (netIfaceUp(IFACE_NAME) == false) {
		close(sock);
		return false;
	}

	if (inet_pton(AF_INET, nsjconf->iface_vs_gw, &addr) != 1) {
		PLOG_E("Cannot convert '%s' into a IPv4 GW address", nsjconf->iface_vs_gw);
		close(sock);
		return false;
	}
	if (addr.s_addr == INADDR_ANY) {
		LOG_D("Gateway address for '%s' is not set", IFACE_NAME);
		close(sock);
		return true;
	}

	struct rtentry rt;
	memset(&rt, '\0', sizeof(rt));

	struct sockaddr_in* sdest = (struct sockaddr_in*)(&rt.rt_dst);
	struct sockaddr_in* smask = (struct sockaddr_in*)(&rt.rt_genmask);
	struct sockaddr_in* sgate = (struct sockaddr_in*)(&rt.rt_gateway);
	sdest->sin_family = AF_INET;
	sdest->sin_addr.s_addr = INADDR_ANY;
	smask->sin_family = AF_INET;
	smask->sin_addr.s_addr = INADDR_ANY;
	sgate->sin_family = AF_INET;
	sgate->sin_addr = addr;

	rt.rt_flags = RTF_UP | RTF_GATEWAY;
	rt.rt_dev = IFACE_NAME;

	if (ioctl(sock, SIOCADDRT, &rt) == -1) {
		PLOG_E("ioctl(SIOCADDRT, '%s')", nsjconf->iface_vs_gw);
		close(sock);
		return false;
	}

	close(sock);
	return true;
}

bool netInitNsFromChild(struct nsjconf_t* nsjconf)
{
	if (nsjconf->clone_newnet == false) {
		return true;
	}
	if (nsjconf->iface_no_lo == false) {
		if (netIfaceUp("lo") == false) {
			return false;
		}
	}
	if (nsjconf->iface_vs) {
		if (netConfigureVs(nsjconf) == false) {
			return false;
		}
	}
	return true;
}
