/*

   nsjail - CLONE_NEWUSER routines
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

#include "user.h"

#include <errno.h>
#include <fcntl.h>
#include <grp.h>
#include <limits.h>
#include <linux/securebits.h>
#include <pwd.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/prctl.h>
#include <sys/queue.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

#include "common.h"
#include "log.h"
#include "subproc.h"
#include "util.h"

static bool userSetResGid(gid_t gid)
{
	LOG_D("setresgid(%d)", gid);
#if defined(__NR_setresgid32)
	if (syscall(__NR_setresgid32, (uintptr_t)gid, (uintptr_t)gid, (uintptr_t)gid) == -1) {
		PLOG_W("setresgid32(%d)", (int)gid);
		return false;
	}
#else /* defined(__NR_setresgid32) */
	if (syscall(__NR_setresgid, (uintptr_t)gid, (uintptr_t)gid, (uintptr_t)gid) == -1) {
		PLOG_W("setresgid(%d)", gid);
		return false;
	}
#endif /* defined(__NR_setresuid32) */
	return true;
}

static bool userSetResUid(uid_t uid)
{
	LOG_D("setresuid(%d)", uid);
#if defined(__NR_setresuid32)
	if (syscall(__NR_setresuid32, (uintptr_t)uid, (uintptr_t)uid, (uintptr_t)uid) == -1) {
		PLOG_W("setresuid32(%d)", (int)uid);
		return false;
	}
#else /* defined(__NR_setresuid32) */
	if (syscall(__NR_setresuid, (uintptr_t)uid, (uintptr_t)uid, (uintptr_t)uid) == -1) {
		PLOG_W("setresuid(%d)", uid);
		return false;
	}
#endif /* defined(__NR_setresuid32) */
	return true;
}

static bool userSetGroups(pid_t pid)
{
	/*
	 * No need to write 'deny' to /proc/pid/setgroups if our euid==0, as writing to
	 * uid_map/gid_map will succeed anyway
	 */
	if (geteuid() == 0) {
		return true;
	}

	char fname[PATH_MAX];
	snprintf(fname, sizeof(fname), "/proc/%d/setgroups", pid);
	const char* denystr = "deny";
	if (!utilWriteBufToFile(fname, denystr, strlen(denystr), O_WRONLY | O_CLOEXEC)) {
		LOG_E("utilWriteBufToFile('%s', '%s') failed", fname, denystr);
		return false;
	}
	return true;
}

static bool userUidMapSelf(struct nsjconf_t* nsjconf, pid_t pid)
{
	char fname[PATH_MAX];
	snprintf(fname, sizeof(fname), "/proc/%d/uid_map", pid);

	char map[4096] = { [0] = '\0' };

	struct idmap_t* p;
	TAILQ_FOREACH(p, &nsjconf->uids, pointers)
	{
		if (p->is_newidmap) {
			continue;
		}
		utilSSnPrintf(map, sizeof(map), "%lu %lu %zu\n", (unsigned long)p->inside_id,
		    (unsigned long)p->outside_id, p->count);
	}

	if (strlen(map) == 0) {
		return true;
	}

	LOG_D("Writing '%s' to '%s'", map, fname);
	if (!utilWriteBufToFile(fname, map, strlen(map), O_WRONLY | O_CLOEXEC)) {
		LOG_E("utilWriteBufToFile('%s', '%s') failed", fname, map);
		return false;
	}

	return true;
}

static bool userGidMapSelf(struct nsjconf_t* nsjconf, pid_t pid)
{
	char fname[PATH_MAX];
	snprintf(fname, sizeof(fname), "/proc/%d/gid_map", pid);

	char map[4096] = { [0] = '\0' };

	struct idmap_t* p;
	TAILQ_FOREACH(p, &nsjconf->gids, pointers)
	{
		if (p->is_newidmap) {
			continue;
		}
		utilSSnPrintf(map, sizeof(map), "%lu %lu %zu\n", (unsigned long)p->inside_id,
		    (unsigned long)p->outside_id, p->count);
	}

	if (strlen(map) == 0) {
		return true;
	}

	LOG_D("Writing '%s' to '%s'", map, fname);
	if (!utilWriteBufToFile(fname, map, strlen(map), O_WRONLY | O_CLOEXEC)) {
		LOG_E("utilWriteBufToFile('%s', '%s') failed", fname, map);
		return false;
	}

	return true;
}

/* Use /usr/bin/newgidmap for writing the gid map */
static bool userGidMapExternal(struct nsjconf_t* nsjconf, pid_t pid UNUSED)
{
	size_t idx = 0;

	const char* argv[1024];
	char parms[1024][256];

	argv[idx++] = "/usr/bin/newgidmap";

	snprintf(parms[idx], sizeof(parms[idx]), "%u", (unsigned)pid);
	argv[idx] = parms[idx];
	idx++;

	struct idmap_t* p;
	bool use = false;
	TAILQ_FOREACH(p, &nsjconf->gids, pointers)
	{
		if (p->is_newidmap == false) {
			continue;
		}
		if ((idx + 4) >= ARRAYSIZE(argv)) {
			LOG_W("Too many arguments for '/usr/bin/newgidmap'");
			return false;
		}
		use = true;

		snprintf(parms[idx], sizeof(parms[idx]), "%u", (unsigned)p->inside_id);
		argv[idx] = parms[idx];
		idx++;

		snprintf(parms[idx], sizeof(parms[idx]), "%u", (unsigned)p->outside_id);
		argv[idx] = parms[idx];
		idx++;

		snprintf(parms[idx], sizeof(parms[idx]), "%zu", p->count);
		argv[idx] = parms[idx];
		idx++;
	}

	argv[idx] = NULL;

	if (!use) {
		return true;
	}

	if (subprocSystem(argv, environ) != 0) {
		LOG_E("'/usr/bin/newgidmap' failed");
		return false;
	}

	return true;
}

/* Use /usr/bin/newuidmap for writing the uid map */
static bool userUidMapExternal(struct nsjconf_t* nsjconf, pid_t pid UNUSED)
{
	size_t idx = 0;

	const char* argv[1024];
	char parms[1024][256];

	argv[idx++] = "/usr/bin/newuidmap";

	snprintf(parms[idx], sizeof(parms[idx]), "%u", (unsigned)pid);
	argv[idx] = parms[idx];
	idx++;

	bool use = false;
	struct idmap_t* p;
	TAILQ_FOREACH(p, &nsjconf->uids, pointers)
	{
		if (p->is_newidmap == false) {
			continue;
		}
		if ((idx + 4) >= ARRAYSIZE(argv)) {
			LOG_W("Too many arguments for '/usr/bin/newuidmap'");
			return false;
		}
		use = true;

		snprintf(parms[idx], sizeof(parms[idx]), "%u", (unsigned)p->inside_id);
		argv[idx] = parms[idx];
		idx++;

		snprintf(parms[idx], sizeof(parms[idx]), "%u", (unsigned)p->outside_id);
		argv[idx] = parms[idx];
		idx++;

		snprintf(parms[idx], sizeof(parms[idx]), "%zu", p->count);
		argv[idx] = parms[idx];
		idx++;
	}

	argv[idx] = NULL;

	if (!use) {
		return true;
	}

	if (subprocSystem(argv, environ) != 0) {
		LOG_E("'/usr/bin/newuidmap' failed");
		return false;
	}

	return true;
}

static bool userUidGidMap(struct nsjconf_t* nsjconf, pid_t pid)
{
	if (!userGidMapSelf(nsjconf, pid)) {
		return false;
	}
	if (!userGidMapExternal(nsjconf, pid)) {
		return false;
	}
	if (!userUidMapSelf(nsjconf, pid)) {
		return false;
	}
	if (!userUidMapExternal(nsjconf, pid)) {
		return false;
	}
	return true;
}

bool userInitNsFromParent(struct nsjconf_t* nsjconf, pid_t pid)
{
	if (userSetGroups(pid) == false) {
		return false;
	}
	if (nsjconf->clone_newuser == false) {
		return true;
	}
	if (userUidGidMap(nsjconf, pid) == false) {
		return false;
	}
	return true;
}

bool userInitNsFromChild(struct nsjconf_t* nsjconf)
{
	/*
	 * Best effort because of /proc/self/setgroups
	 */
	LOG_D("setgroups(0, NULL)");
	gid_t* group_list = NULL;
	if (setgroups(0, group_list) == -1) {
		PLOG_D("setgroups(NULL) failed");
	}

	/*
	 * Make sure all capabilities are retained after the subsequent setuid/setgid, as they will
	 * be needed for privileged operations: mounts, uts change etc.
	 */
	if (prctl(PR_SET_SECUREBITS, SECBIT_KEEP_CAPS | SECBIT_NO_SETUID_FIXUP, 0UL, 0UL, 0UL)
	    == -1) {
		PLOG_E("prctl(PR_SET_SECUREBITS, SECBIT_KEEP_CAPS | SECBIT_NO_SETUID_FIXUP)");
		return false;
	}

	if (!userSetResGid(TAILQ_FIRST(&nsjconf->gids)->inside_id)) {
		PLOG_E("setresgid(%u)", TAILQ_FIRST(&nsjconf->gids)->inside_id);
		return false;
	}
	if (!userSetResUid(TAILQ_FIRST(&nsjconf->uids)->inside_id)) {
		PLOG_E("setresuid(%u)", TAILQ_FIRST(&nsjconf->uids)->inside_id);
		return false;
	}

	return true;
}

static uid_t cmdParseUid(const char* id)
{
	if (id == NULL || strlen(id) == 0) {
		return getuid();
	}
	struct passwd* pw = getpwnam(id);
	if (pw != NULL) {
		return pw->pw_uid;
	}
	if (utilIsANumber(id)) {
		return (uid_t)strtoull(id, NULL, 0);
	}
	return -1;
}

static gid_t cmdParseGid(const char* id)
{
	if (id == NULL || strlen(id) == 0) {
		return getgid();
	}
	struct group* gr = getgrnam(id);
	if (gr != NULL) {
		return gr->gr_gid;
	}
	if (utilIsANumber(id)) {
		return (gid_t)strtoull(id, NULL, 0);
	}
	return -1;
}

bool userParseId(struct nsjconf_t* nsjconf, const char* i_id, const char* o_id, size_t cnt,
    bool is_gid, bool is_newidmap)
{
	uid_t inside_id;
	uid_t outside_id;

	if (is_gid) {
		inside_id = cmdParseGid(i_id);
		if (inside_id == (uid_t)-1) {
			LOG_W("Cannot parse '%s' as GID", i_id);
			return false;
		}
		outside_id = cmdParseGid(o_id);
		if (inside_id == (uid_t)-1) {
			LOG_W("Cannot parse '%s' as GID", o_id);
			return false;
		}
	} else {
		inside_id = cmdParseUid(i_id);
		if (inside_id == (uid_t)-1) {
			LOG_W("Cannot parse '%s' as UID", i_id);
			return false;
		}
		outside_id = cmdParseUid(o_id);
		if (inside_id == (uid_t)-1) {
			LOG_W("Cannot parse '%s' as UID", o_id);
			return false;
		}
	}

	struct idmap_t* p = utilMalloc(sizeof(struct idmap_t));
	p->inside_id = inside_id;
	p->outside_id = outside_id;
	p->count = cnt;
	p->is_newidmap = is_newidmap;

	if (is_gid) {
		TAILQ_INSERT_TAIL(&nsjconf->gids, p, pointers);
	} else {
		TAILQ_INSERT_TAIL(&nsjconf->uids, p, pointers);
	}

	return true;
}
