/*
   Kafel - syscalls (mips64)
   -----------------------------------------

   Copyright 2016 Google Inc. All Rights Reserved.

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

#include "../syscall.h"

#include <stddef.h>

#define ARG_0 0
#define ARG_1 1
#define ARG_2 2
#define ARG_3 3
#define ARG_4 4
#define ARG_5 5

#define NORMAL false

const struct syscall_descriptor mips64_syscall_list[] = {
    {"accept",
      5042,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"upeer_sockaddr", 8},
             [ARG_2] = {"upeer_addrlen", 8},
     }},
    {"accept4",
      5293,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"upeer_sockaddr", 8},
             [ARG_2] = {"upeer_addrlen", 8}, [ARG_3] = {"flags", 4},
     }},
    {"acct",
      5158,
     NORMAL,
     {
             [ARG_0] = {"name", 8},
     }},
    {"add_key",
      5239,
     NORMAL,
     {
             [ARG_0] = {"_type", 8}, [ARG_1] = {"_description", 8},
             [ARG_2] = {"_payload", 8}, [ARG_3] = {"plen", 8},
             [ARG_4] = {"ringid", 4},
     }},
    {"adjtimex",
      5154,
     NORMAL,
     {
             [ARG_0] = {"txc_p", 8},
     }},
    {"bind",
      5048,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"umyaddr", 8},
             [ARG_2] = {"addrlen", 4},
     }},
    {"bpf",
      5315,
     NORMAL,
     {
             [ARG_0] = {"cmd", 4}, [ARG_1] = {"uattr", 8},
             [ARG_2] = {"size", 4},
     }},
    {"brk",
      5012,
     NORMAL,
     {
             [ARG_0] = {"brk", 8},
     }},
    {"capget",
      5123,
     NORMAL,
     {
             [ARG_0] = {"header", 8}, [ARG_1] = {"dataptr", 8},
     }},
    {"capset",
      5124,
     NORMAL,
     {
             [ARG_0] = {"header", 8}, [ARG_1] = {"data", 8},
     }},
    {"chdir",
      5078,
     NORMAL,
     {
             [ARG_0] = {"filename", 8},
     }},
    {"chroot",
      5156,
     NORMAL,
     {
             [ARG_0] = {"filename", 8},
     }},
    {"clock_adjtime",
      5300,
     NORMAL,
     {
             [ARG_0] = {"which_clock", 4}, [ARG_1] = {"utx", 8},
     }},
    {"clock_getres",
      5223,
     NORMAL,
     {
             [ARG_0] = {"which_clock", 4}, [ARG_1] = {"tp", 8},
     }},
    {"clock_gettime",
      5222,
     NORMAL,
     {
             [ARG_0] = {"which_clock", 4}, [ARG_1] = {"tp", 8},
     }},
    {"clock_nanosleep",
      5224,
     NORMAL,
     {
             [ARG_0] = {"which_clock", 4}, [ARG_1] = {"flags", 4},
             [ARG_2] = {"rqtp", 8}, [ARG_3] = {"rmtp", 8},
     }},
    {"clock_settime",
      5221,
     NORMAL,
     {
             [ARG_0] = {"which_clock", 4}, [ARG_1] = {"tp", 8},
     }},
    {"clone",
      5055,
     NORMAL,
     {
             [ARG_0] = {"clone_flags", 8}, [ARG_1] = {"newsp", 8},
             [ARG_2] = {"parent_tidptr", 8}, [ARG_3] = {"child_tidptr", 8},
             [ARG_4] = {"tls", 8},
     }},
    {"close",
      5003,
     NORMAL,
     {
             [ARG_0] = {"fd", 4},
     }},
    {"connect",
      5041,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"uservaddr", 8},
             [ARG_2] = {"addrlen", 4},
     }},
    {"copy_file_range",
     285,
     NORMAL,
     {
             [ARG_0] = {"fd_in", 4}, [ARG_1] = {"off_in", 8},
             [ARG_2] = {"fd_out", 4}, [ARG_3] = {"off_out", 8},
             [ARG_4] = {"len", 8}, [ARG_5] = {"flags", 4},
     }},
    {"delete_module",
      5169,
     NORMAL,
     {
             [ARG_0] = {"name_user", 8}, [ARG_1] = {"flags", 4},
     }},
    {"dup",
      5031,
     NORMAL,
     {
             [ARG_0] = {"fildes", 4},
     }},
    {"dup3",
      5286,
     NORMAL,
     {
             [ARG_0] = {"oldfd", 4}, [ARG_1] = {"newfd", 4},
             [ARG_2] = {"flags", 4},
     }},
    {"epoll_create1",
      5285,
     NORMAL,
     {
             [ARG_0] = {"flags", 4},
     }},
    {"epoll_ctl",
      5208,
     NORMAL,
     {
             [ARG_0] = {"epfd", 4}, [ARG_1] = {"op", 4}, [ARG_2] = {"fd", 4},
             [ARG_3] = {"event", 8},
     }},
    {"epoll_pwait",
      5272,
     NORMAL,
     {
             [ARG_0] = {"epfd", 4}, [ARG_1] = {"events", 8},
             [ARG_2] = {"maxevents", 4}, [ARG_3] = {"timeout", 4},
             [ARG_4] = {"sigmask", 8}, [ARG_5] = {"sigsetsize", 8},
     }},
    {"eventfd2",
      5284,
     NORMAL,
     {
             [ARG_0] = {"count", 4}, [ARG_1] = {"flags", 4},
     }},
    {"execve",
      5057,
     NORMAL,
     {
             [ARG_0] = {"filename", 8}, [ARG_1] = {"argv", 8},
             [ARG_2] = {"envp", 8},
     }},
    {"execveat",
      5316,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"filename", 8},
             [ARG_2] = {"argv", 8}, [ARG_3] = {"envp", 8},
             [ARG_4] = {"flags", 4},
     }},
    {"exit",
      5058,
     NORMAL,
     {
             [ARG_0] = {"error_code", 4},
     }},
    {"exit_group",
      5205,
     NORMAL,
     {
             [ARG_0] = {"error_code", 4},
     }},
    {"faccessat",
      5259,
     NORMAL,
     {
             [ARG_0] = {"dfd", 4}, [ARG_1] = {"filename", 8},
             [ARG_2] = {"mode", 4},
     }},
    {"fadvise64",
      5215,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"offset", 8}, [ARG_2] = {"len", 8},
             [ARG_3] = {"advice", 4},
     }},
    {"fallocate",
      5279,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"mode", 4},
             [ARG_2] = {"offset", 8}, [ARG_3] = {"len", 8},
     }},
    {"fanotify_init",
      5295,
     NORMAL,
     {
             [ARG_0] = {"flags", 4}, [ARG_1] = {"event_f_flags", 4},
     }},
    {"fanotify_mark",
      5296,
     NORMAL,
     {
             [ARG_0] = {"fanotify_fd", 4}, [ARG_1] = {"flags", 4},
             [ARG_2] = {"mask", 8}, [ARG_3] = {"dfd", 4},
             [ARG_4] = {"pathname", 8},
     }},
    {"fchdir",
      5079,
     NORMAL,
     {
             [ARG_0] = {"fd", 4},
     }},
    {"fchmod",
      5089,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"mode", 2},
     }},
    {"fchmodat",
      5258,
     NORMAL,
     {
             [ARG_0] = {"dfd", 4}, [ARG_1] = {"filename", 8},
             [ARG_2] = {"mode", 2},
     }},
    {"fchown",
      5091,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"user", 4}, [ARG_2] = {"group", 4},
     }},
    {"fchownat",
      5250,
     NORMAL,
     {
             [ARG_0] = {"dfd", 4}, [ARG_1] = {"filename", 8},
             [ARG_2] = {"user", 4}, [ARG_3] = {"group", 4},
             [ARG_4] = {"flag", 4},
     }},
    {"fcntl",
      5070,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"cmd", 4}, [ARG_2] = {"arg", 8},
     }},
    {"fdatasync",
      5073,
     NORMAL,
     {
             [ARG_0] = {"fd", 4},
     }},
    {"fgetxattr",
      5185,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"name", 8}, [ARG_2] = {"value", 8},
             [ARG_3] = {"size", 8},
     }},
    {"finit_module",
      5307,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"uargs", 8},
             [ARG_2] = {"flags", 4},
     }},
    {"flistxattr",
      5188,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"list", 8}, [ARG_2] = {"size", 8},
     }},
    {"flock",
      5071,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"cmd", 4},
     }},
    {"fremovexattr",
     16,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"name", 8},
     }},
    {"fsetxattr",
      5182,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"name", 8}, [ARG_2] = {"value", 8},
             [ARG_3] = {"size", 8}, [ARG_4] = {"flags", 4},
     }},
    {"fstatfs",
      5135,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"buf", 8},
     }},
    {"fsync",
      5072,
     NORMAL,
     {
             [ARG_0] = {"fd", 4},
     }},
    {"ftruncate",
      5075,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"length", 8},
     }},
    {"futex",
      5194,
     NORMAL,
     {
             [ARG_0] = {"uaddr", 8}, [ARG_1] = {"op", 4}, [ARG_2] = {"val", 4},
             [ARG_3] = {"utime", 8}, [ARG_4] = {"uaddr2", 8},
             [ARG_5] = {"val3", 4},
     }},
    {"getcpu",
      5271,
     NORMAL,
     {
             [ARG_0] = {"cpup", 8}, [ARG_1] = {"nodep", 8},
             [ARG_2] = {"unused", 8},
     }},
    {"getcwd",
      5077,
     NORMAL,
     {
             [ARG_0] = {"buf", 8}, [ARG_1] = {"size", 8},
     }},
    {"getdents64",
      5308,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"dirent", 8},
             [ARG_2] = {"count", 4},
     }},
    {"getegid", 177, NORMAL, {}},
    {"geteuid", 175, NORMAL, {}},
    {"getgid", 176, NORMAL, {}},
    {"getgroups",
     158,
     NORMAL,
     {
             [ARG_0] = {"gidsetsize", 4}, [ARG_1] = {"grouplist", 8},
     }},
    {"getitimer",
      5035,
     NORMAL,
     {
             [ARG_0] = {"which", 4}, [ARG_1] = {"value", 8},
     }},
    {"get_mempolicy",
      5228,
     NORMAL,
     {
             [ARG_0] = {"policy", 8}, [ARG_1] = {"nmask", 8},
             [ARG_2] = {"maxnode", 8}, [ARG_3] = {"addr", 8},
             [ARG_4] = {"flags", 8},
     }},
    {"getpeername",
      5051,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"usockaddr", 8},
             [ARG_2] = {"usockaddr_len", 8},
     }},
    {"getpgid",
      5119,
     NORMAL,
     {
             [ARG_0] = {"pid", 4},
     }},
    {"getpid", 172, NORMAL, {}},
    {"getppid", 173, NORMAL, {}},
    {"getpriority",
     141,
     NORMAL,
     {
             [ARG_0] = {"which", 4}, [ARG_1] = {"who", 4},
     }},
    {"getrandom",
      5313,
     NORMAL,
     {
             [ARG_0] = {"buf", 8}, [ARG_1] = {"count", 8},
             [ARG_2] = {"flags", 4},
     }},
    {"getresgid",
      5118,
     NORMAL,
     {
             [ARG_0] = {"rgidp", 8}, [ARG_1] = {"egidp", 8},
             [ARG_2] = {"sgidp", 8},
     }},
    {"getresuid",
      5116,
     NORMAL,
     {
             [ARG_0] = {"ruidp", 8}, [ARG_1] = {"euidp", 8},
             [ARG_2] = {"suidp", 8},
     }},
    {"getrlimit",
      5095,
     NORMAL,
     {
             [ARG_0] = {"resource", 4}, [ARG_1] = {"rlim", 8},
     }},
    {"get_robust_list",
      5269,
     NORMAL,
     {
             [ARG_0] = {"pid", 4}, [ARG_1] = {"head_ptr", 8},
             [ARG_2] = {"len_ptr", 8},
     }},
    {"getrusage",
      5096,
     NORMAL,
     {
             [ARG_0] = {"who", 4}, [ARG_1] = {"ru", 8},
     }},
    {"getsid",
      5122,
     NORMAL,
     {
             [ARG_0] = {"pid", 4},
     }},
    {"getsockname",
      5050,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"usockaddr", 8},
             [ARG_2] = {"usockaddr_len", 8},
     }},
    {"getsockopt",
      5054,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"level", 4},
             [ARG_2] = {"optname", 4}, [ARG_3] = {"optval", 8},
             [ARG_4] = {"optlen", 8},
     }},
    {"gettid", 178, NORMAL, {}},
    {"gettimeofday",
     169,
     NORMAL,
     {
             [ARG_0] = {"tv", 8}, [ARG_1] = {"tz", 8},
     }},
    {"getuid", 174, NORMAL, {}},
    {"getxattr",
     8,
     NORMAL,
     {
             [ARG_0] = {"pathname", 8}, [ARG_1] = {"name", 8},
             [ARG_2] = {"value", 8}, [ARG_3] = {"size", 8},
     }},
    {"init_module",
      5168,
     NORMAL,
     {
             [ARG_0] = {"umod", 8}, [ARG_1] = {"len", 8},
             [ARG_2] = {"uargs", 8},
     }},
    {"inotify_add_watch",
      5244,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"pathname", 8},
             [ARG_2] = {"mask", 4},
     }},
    {"inotify_init1",
     26,
     NORMAL,
     {
             [ARG_0] = {"flags", 4},
     }},
    {"inotify_rm_watch",
      5245,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"wd", 4},
     }},
    {"io_cancel",
      5204,
     NORMAL,
     {
             [ARG_0] = {"ctx_id", 8}, [ARG_1] = {"iocb", 8},
             [ARG_2] = {"result", 8},
     }},
    {"ioctl",
      5015,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"cmd", 4}, [ARG_2] = {"arg", 8},
     }},
    {"io_destroy",
      5201,
     NORMAL,
     {
             [ARG_0] = {"ctx", 8},
     }},
    {"io_getevents",
      5202,
     NORMAL,
     {
             [ARG_0] = {"ctx_id", 8}, [ARG_1] = {"min_nr", 8},
             [ARG_2] = {"nr", 8}, [ARG_3] = {"events", 8},
             [ARG_4] = {"timeout", 8},
     }},
    {"ioprio_get",
      5274,
     NORMAL,
     {
             [ARG_0] = {"which", 4}, [ARG_1] = {"who", 4},
     }},
    {"ioprio_set",
      5273,
     NORMAL,
     {
             [ARG_0] = {"which", 4}, [ARG_1] = {"who", 4},
             [ARG_2] = {"ioprio", 4},
     }},
    {"io_setup",
      5200,
     NORMAL,
     {
             [ARG_0] = {"nr_events", 4}, [ARG_1] = {"ctxp", 8},
     }},
    {"io_submit",
      5203,
     NORMAL,
     {
             [ARG_0] = {"ctx_id", 8}, [ARG_1] = {"nr", 8},
             [ARG_2] = {"iocbpp", 8},
     }},
    {"kcmp",
      5306,
     NORMAL,
     {
             [ARG_0] = {"pid1", 4}, [ARG_1] = {"pid2", 4},
             [ARG_2] = {"type", 4}, [ARG_3] = {"idx1", 8},
             [ARG_4] = {"idx2", 8},
     }},
    {"kexec_load",
      5270,
     NORMAL,
     {
             [ARG_0] = {"entry", 8}, [ARG_1] = {"nr_segments", 8},
             [ARG_2] = {"segments", 8}, [ARG_3] = {"flags", 8},
     }},
    {"keyctl",
      5241,
     NORMAL,
     {
             [ARG_0] = {"option", 4}, [ARG_1] = {"arg2", 8},
             [ARG_2] = {"arg3", 8}, [ARG_3] = {"arg4", 8},
             [ARG_4] = {"arg5", 8},
     }},
    {"kill",
      5060,
     NORMAL,
     {
             [ARG_0] = {"pid", 4}, [ARG_1] = {"sig", 4},
     }},
    {"lgetxattr",
      5184,
     NORMAL,
     {
             [ARG_0] = {"pathname", 8}, [ARG_1] = {"name", 8},
             [ARG_2] = {"value", 8}, [ARG_3] = {"size", 8},
     }},
    {"linkat",
      5255,
     NORMAL,
     {
             [ARG_0] = {"olddfd", 4}, [ARG_1] = {"oldname", 8},
             [ARG_2] = {"newdfd", 4}, [ARG_3] = {"newname", 8},
             [ARG_4] = {"flags", 4},
     }},
    {"listen",
      5049,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"backlog", 4},
     }},
    {"listxattr",
      5186,
     NORMAL,
     {
             [ARG_0] = {"pathname", 8}, [ARG_1] = {"list", 8},
             [ARG_2] = {"size", 8},
     }},
    {"llistxattr",
      5187,
     NORMAL,
     {
             [ARG_0] = {"pathname", 8}, [ARG_1] = {"list", 8},
             [ARG_2] = {"size", 8},
     }},
    {"lookup_dcookie",
      5206,
     NORMAL,
     {
             [ARG_0] = {"cookie64", 8}, [ARG_1] = {"buf", 8},
             [ARG_2] = {"len", 8},
     }},
    {"lremovexattr",
      5190,
     NORMAL,
     {
             [ARG_0] = {"pathname", 8}, [ARG_1] = {"name", 8},
     }},
    {"lseek",
      5008,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"offset", 8},
             [ARG_2] = {"whence", 4},
     }},
    {"lsetxattr",
      5181,
     NORMAL,
     {
             [ARG_0] = {"pathname", 8}, [ARG_1] = {"name", 8},
             [ARG_2] = {"value", 8}, [ARG_3] = {"size", 8},
             [ARG_4] = {"flags", 4},
     }},
    {"madvise",
      5027,
     NORMAL,
     {
             [ARG_0] = {"start", 8}, [ARG_1] = {"len_in", 8},
             [ARG_2] = {"behavior", 4},
     }},
    {"mbind",
      5227,
     NORMAL,
     {
             [ARG_0] = {"start", 8}, [ARG_1] = {"len", 8},
             [ARG_2] = {"mode", 8}, [ARG_3] = {"nmask", 8},
             [ARG_4] = {"maxnode", 8}, [ARG_5] = {"flags", 4},
     }},
    {"membarrier",
      5318,
     NORMAL,
     {
             [ARG_0] = {"cmd", 4}, [ARG_1] = {"flags", 4},
     }},
    {"memfd_create",
      5314,
     NORMAL,
     {
             [ARG_0] = {"uname", 8}, [ARG_1] = {"flags", 4},
     }},
    {"migrate_pages",
      5246,
     NORMAL,
     {
             [ARG_0] = {"pid", 4}, [ARG_1] = {"maxnode", 8},
             [ARG_2] = {"old_nodes", 8}, [ARG_3] = {"new_nodes", 8},
     }},
    {"mincore",
      5026,
     NORMAL,
     {
             [ARG_0] = {"start", 8}, [ARG_1] = {"len", 8}, [ARG_2] = {"vec", 8},
     }},
    {"mkdirat",
      5248,
     NORMAL,
     {
             [ARG_0] = {"dfd", 4}, [ARG_1] = {"pathname", 8},
             [ARG_2] = {"mode", 2},
     }},
    {"mknodat",
      5249,
     NORMAL,
     {
             [ARG_0] = {"dfd", 4}, [ARG_1] = {"filename", 8},
             [ARG_2] = {"mode", 2}, [ARG_3] = {"dev", 4},
     }},
    {"mlock",
      5146,
     NORMAL,
     {
             [ARG_0] = {"start", 8}, [ARG_1] = {"len", 8},
     }},
    {"mlock2",
      5319,
     NORMAL,
     {
             [ARG_0] = {"start", 8}, [ARG_1] = {"len", 8},
             [ARG_2] = {"flags", 4},
     }},
    {"mlockall",
      5148,
     NORMAL,
     {
             [ARG_0] = {"flags", 4},
     }},
    {"mmap",
      5009,
     NORMAL,
     {
             [ARG_0] = {"addr", 8}, [ARG_1] = {"len", 8}, [ARG_2] = {"prot", 8},
             [ARG_3] = {"flags", 8}, [ARG_4] = {"fd", 8}, [ARG_5] = {"off", 8},
     }},
    {"mount",
      5160,
     NORMAL,
     {
             [ARG_0] = {"dev_name", 8}, [ARG_1] = {"dir_name", 8},
             [ARG_2] = {"type", 8}, [ARG_3] = {"flags", 8},
             [ARG_4] = {"data", 8},
     }},
    {"move_pages",
      5267,
     NORMAL,
     {
             [ARG_0] = {"pid", 4}, [ARG_1] = {"nr_pages", 8},
             [ARG_2] = {"pages", 8}, [ARG_3] = {"nodes", 8},
             [ARG_4] = {"status", 8}, [ARG_5] = {"flags", 4},
     }},
    {"mprotect",
      5010,
     NORMAL,
     {
             [ARG_0] = {"start", 8}, [ARG_1] = {"len", 8},
             [ARG_2] = {"prot", 8},
     }},
    {"mq_getsetattr",
      5235,
     NORMAL,
     {
             [ARG_0] = {"mqdes", 4}, [ARG_1] = {"u_mqstat", 8},
             [ARG_2] = {"u_omqstat", 8},
     }},
    {"mq_notify",
      5234,
     NORMAL,
     {
             [ARG_0] = {"mqdes", 4}, [ARG_1] = {"u_notification", 8},
     }},
    {"mq_open",
      5230,
     NORMAL,
     {
             [ARG_0] = {"u_name", 8}, [ARG_1] = {"oflag", 4},
             [ARG_2] = {"mode", 2}, [ARG_3] = {"u_attr", 8},
     }},
    {"mq_timedreceive",
      5233,
     NORMAL,
     {
             [ARG_0] = {"mqdes", 4}, [ARG_1] = {"u_msg_ptr", 8},
             [ARG_2] = {"msg_len", 8}, [ARG_3] = {"u_msg_prio", 8},
             [ARG_4] = {"u_abs_timeout", 8},
     }},
    {"mq_timedsend",
      5232,
     NORMAL,
     {
             [ARG_0] = {"mqdes", 4}, [ARG_1] = {"u_msg_ptr", 8},
             [ARG_2] = {"msg_len", 8}, [ARG_3] = {"msg_prio", 4},
             [ARG_4] = {"u_abs_timeout", 8},
     }},
    {"mq_unlink",
      5231,
     NORMAL,
     {
             [ARG_0] = {"u_name", 8},
     }},
    {"mremap",
      5024,
     NORMAL,
     {
             [ARG_0] = {"addr", 8}, [ARG_1] = {"old_len", 8},
             [ARG_2] = {"new_len", 8}, [ARG_3] = {"flags", 8},
             [ARG_4] = {"new_addr", 8},
     }},
    {"msgctl",
      5069,
     NORMAL,
     {
             [ARG_0] = {"msqid", 4}, [ARG_1] = {"cmd", 4}, [ARG_2] = {"buf", 8},
     }},
    {"msgget",
      5066,
     NORMAL,
     {
             [ARG_0] = {"key", 4}, [ARG_1] = {"msgflg", 4},
     }},
    {"msgrcv",
      5068,
     NORMAL,
     {
             [ARG_0] = {"msqid", 4}, [ARG_1] = {"msgp", 8},
             [ARG_2] = {"msgsz", 8}, [ARG_3] = {"msgtyp", 8},
             [ARG_4] = {"msgflg", 4},
     }},
    {"msgsnd",
      5067,
     NORMAL,
     {
             [ARG_0] = {"msqid", 4}, [ARG_1] = {"msgp", 8},
             [ARG_2] = {"msgsz", 8}, [ARG_3] = {"msgflg", 4},
     }},
    {"msync",
      5025,
     NORMAL,
     {
             [ARG_0] = {"start", 8}, [ARG_1] = {"len", 8},
             [ARG_2] = {"flags", 4},
     }},
    {"munlock",
      5147,
     NORMAL,
     {
             [ARG_0] = {"start", 8}, [ARG_1] = {"len", 8},
     }},
    {"munlockall", 231, NORMAL, {}},
    {"munmap",
     215,
     NORMAL,
     {
             [ARG_0] = {"addr", 8}, [ARG_1] = {"len", 8},
     }},
    {"name_to_handle_at",
      5298,
     NORMAL,
     {
             [ARG_0] = {"dfd", 4}, [ARG_1] = {"name", 8},
             [ARG_2] = {"handle", 8}, [ARG_3] = {"mnt_id", 8},
             [ARG_4] = {"flag", 4},
     }},
    {"nanosleep",
      5034,
     NORMAL,
     {
             [ARG_0] = {"rqtp", 8}, [ARG_1] = {"rmtp", 8},
     }},
    {"newfstat",
     80,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"statbuf", 8},
     }},
    {"newfstatat",
      5252,
     NORMAL,
     {
             [ARG_0] = {"dfd", 4}, [ARG_1] = {"filename", 8},
             [ARG_2] = {"statbuf", 8}, [ARG_3] = {"flag", 4},
     }},
    {"newuname",
     160,
     NORMAL,
     {
             [ARG_0] = {"name", 8},
     }},
    {"nfsservctl",
      5173,
     NORMAL,
     {
             [ARG_0] = {"cmd", 4}, [ARG_1] = {"argp", 8}, [ARG_2] = {"resp", 8},
     }},
    {"openat",
      5247,
     NORMAL,
     {
             [ARG_0] = {"dfd", 4}, [ARG_1] = {"filename", 8},
             [ARG_2] = {"flags", 4}, [ARG_3] = {"mode", 2},
     }},
    {"open_by_handle_at",
      5299,
     NORMAL,
     {
             [ARG_0] = {"mountdirfd", 4}, [ARG_1] = {"handle", 8},
             [ARG_2] = {"flags", 4},
     }},
    {"perf_event_open",
     241,
     NORMAL,
     {
             [ARG_0] = {"attr_uptr", 8}, [ARG_1] = {"pid", 4},
             [ARG_2] = {"cpu", 4}, [ARG_3] = {"group_fd", 4},
             [ARG_4] = {"flags", 8},
     }},
    {"personality",
      5132,
     NORMAL,
     {
             [ARG_0] = {"personality", 4},
     }},
    {"pipe2",
      5287,
     NORMAL,
     {
             [ARG_0] = {"fildes", 8}, [ARG_1] = {"flags", 4},
     }},
    {"pivot_root",
      5151,
     NORMAL,
     {
             [ARG_0] = {"new_root", 8}, [ARG_1] = {"put_old", 8},
     }},
    {"ppoll",
      5261,
     NORMAL,
     {
             [ARG_0] = {"ufds", 8}, [ARG_1] = {"nfds", 4}, [ARG_2] = {"tsp", 8},
             [ARG_3] = {"sigmask", 8}, [ARG_4] = {"sigsetsize", 8},
     }},
    {"prctl",
      5153,
     NORMAL,
     {
             [ARG_0] = {"option", 4}, [ARG_1] = {"arg2", 8},
             [ARG_2] = {"arg3", 8}, [ARG_3] = {"arg4", 8},
             [ARG_4] = {"arg5", 8},
     }},
    {"pread64",
      5016,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"buf", 8}, [ARG_2] = {"count", 8},
             [ARG_3] = {"pos", 8},
     }},
    {"preadv",
      5289,
     NORMAL,
     {
             [ARG_0] = {"fd", 8}, [ARG_1] = {"vec", 8}, [ARG_2] = {"vlen", 8},
             [ARG_3] = {"pos_l", 8}, [ARG_4] = {"pos_h", 8},
     }},
    {"preadv2",
     286,
     NORMAL,
     {
             [ARG_0] = {"fd", 8}, [ARG_1] = {"vec", 8}, [ARG_2] = {"vlen", 8},
             [ARG_3] = {"pos_l", 8}, [ARG_4] = {"pos_h", 8},
             [ARG_5] = {"flags", 4},
     }},
    {"prlimit64",
      5297,
     NORMAL,
     {
             [ARG_0] = {"pid", 4}, [ARG_1] = {"resource", 4},
             [ARG_2] = {"new_rlim", 8}, [ARG_3] = {"old_rlim", 8},
     }},
    {"process_vm_readv",
      5304,
     NORMAL,
     {
             [ARG_0] = {"pid", 4}, [ARG_1] = {"lvec", 8},
             [ARG_2] = {"liovcnt", 8}, [ARG_3] = {"rvec", 8},
             [ARG_4] = {"riovcnt", 8}, [ARG_5] = {"flags", 8},
     }},
    {"process_vm_writev",
      5305,
     NORMAL,
     {
             [ARG_0] = {"pid", 4}, [ARG_1] = {"lvec", 8},
             [ARG_2] = {"liovcnt", 8}, [ARG_3] = {"rvec", 8},
             [ARG_4] = {"riovcnt", 8}, [ARG_5] = {"flags", 8},
     }},
    {"pselect6",
      5260,
     NORMAL,
     {
             [ARG_0] = {"n", 4}, [ARG_1] = {"inp", 8}, [ARG_2] = {"outp", 8},
             [ARG_3] = {"exp", 8}, [ARG_4] = {"tsp", 8}, [ARG_5] = {"sig", 8},
     }},
    {"ptrace",
      5099,
     NORMAL,
     {
             [ARG_0] = {"request", 8}, [ARG_1] = {"pid", 8},
             [ARG_2] = {"addr", 8}, [ARG_3] = {"data", 8},
     }},
    {"pwrite64",
      5017,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"buf", 8}, [ARG_2] = {"count", 8},
             [ARG_3] = {"pos", 8},
     }},
    {"pwritev",
      5290,
     NORMAL,
     {
             [ARG_0] = {"fd", 8}, [ARG_1] = {"vec", 8}, [ARG_2] = {"vlen", 8},
             [ARG_3] = {"pos_l", 8}, [ARG_4] = {"pos_h", 8},
     }},
    {"pwritev2",
     287,
     NORMAL,
     {
             [ARG_0] = {"fd", 8}, [ARG_1] = {"vec", 8}, [ARG_2] = {"vlen", 8},
             [ARG_3] = {"pos_l", 8}, [ARG_4] = {"pos_h", 8},
             [ARG_5] = {"flags", 4},
     }},
    {"quotactl",
      5172,
     NORMAL,
     {
             [ARG_0] = {"cmd", 4}, [ARG_1] = {"special", 8},
             [ARG_2] = {"id", 4}, [ARG_3] = {"addr", 8},
     }},
    {"read",
      5000,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"buf", 8}, [ARG_2] = {"count", 8},
     }},
    {"readahead",
      5179,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"offset", 8},
             [ARG_2] = {"count", 8},
     }},
    {"readlinkat",
      5257,
     NORMAL,
     {
             [ARG_0] = {"dfd", 4}, [ARG_1] = {"pathname", 8},
             [ARG_2] = {"buf", 8}, [ARG_3] = {"bufsiz", 4},
     }},
    {"readv",
      5018,
     NORMAL,
     {
             [ARG_0] = {"fd", 8}, [ARG_1] = {"vec", 8}, [ARG_2] = {"vlen", 8},
     }},
    {"reboot",
      5164,
     NORMAL,
     {
             [ARG_0] = {"magic1", 4}, [ARG_1] = {"magic2", 4},
             [ARG_2] = {"cmd", 4}, [ARG_3] = {"arg", 8},
     }},
    {"recvfrom",
      5044,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"ubuf", 8}, [ARG_2] = {"size", 8},
             [ARG_3] = {"flags", 4}, [ARG_4] = {"addr", 8},
             [ARG_5] = {"addr_len", 8},
     }},
    {"recvmmsg",
      5294,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"mmsg", 8}, [ARG_2] = {"vlen", 4},
             [ARG_3] = {"flags", 4}, [ARG_4] = {"timeout", 8},
     }},
    {"recvmsg",
      5046,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"msg", 8}, [ARG_2] = {"flags", 4},
     }},
    {"remap_file_pages",
      5210,
     NORMAL,
     {
             [ARG_0] = {"start", 8}, [ARG_1] = {"size", 8},
             [ARG_2] = {"prot", 8}, [ARG_3] = {"pgoff", 8},
             [ARG_4] = {"flags", 8},
     }},
    {"removexattr",
      5189,
     NORMAL,
     {
             [ARG_0] = {"pathname", 8}, [ARG_1] = {"name", 8},
     }},
    {"renameat",
      5254,
     NORMAL,
     {
             [ARG_0] = {"olddfd", 4}, [ARG_1] = {"oldname", 8},
             [ARG_2] = {"newdfd", 4}, [ARG_3] = {"newname", 8},
     }},
    {"renameat2",
      5311,
     NORMAL,
     {
             [ARG_0] = {"olddfd", 4}, [ARG_1] = {"oldname", 8},
             [ARG_2] = {"newdfd", 4}, [ARG_3] = {"newname", 8},
             [ARG_4] = {"flags", 4},
     }},
    {"request_key",
      5240,
     NORMAL,
     {
             [ARG_0] = {"_type", 8}, [ARG_1] = {"_description", 8},
             [ARG_2] = {"_callout_info", 8}, [ARG_3] = {"destringid", 4},
     }},
    {"restart_syscall", 128, NORMAL, {}},
    {"rt_sigaction",
      5013,
     NORMAL,
     {
             [ARG_0] = {"sig", 4}, [ARG_1] = {"act", 8}, [ARG_2] = {"oact", 8},
             [ARG_3] = {"sigsetsize", 8},
     }},
    {"rt_sigpending",
      5125,
     NORMAL,
     {
             [ARG_0] = {"uset", 8}, [ARG_1] = {"sigsetsize", 8},
     }},
    {"rt_sigprocmask",
      5014,
     NORMAL,
     {
             [ARG_0] = {"how", 4}, [ARG_1] = {"nset", 8}, [ARG_2] = {"oset", 8},
             [ARG_3] = {"sigsetsize", 8},
     }},
    {"rt_sigqueueinfo",
      5127,
     NORMAL,
     {
             [ARG_0] = {"pid", 4}, [ARG_1] = {"sig", 4}, [ARG_2] = {"uinfo", 8},
     }},
    {"rt_sigreturn", 139, NORMAL, {}},
    {"rt_sigsuspend",
     133,
     NORMAL,
     {
             [ARG_0] = {"unewset", 8}, [ARG_1] = {"sigsetsize", 8},
     }},
    {"rt_sigtimedwait",
      5126,
     NORMAL,
     {
             [ARG_0] = {"uthese", 8}, [ARG_1] = {"uinfo", 8},
             [ARG_2] = {"uts", 8}, [ARG_3] = {"sigsetsize", 8},
     }},
    {"rt_tgsigqueueinfo",
      5291,
     NORMAL,
     {
             [ARG_0] = {"tgid", 4}, [ARG_1] = {"pid", 4}, [ARG_2] = {"sig", 4},
             [ARG_3] = {"uinfo", 8},
     }},
    {"sched_getaffinity",
      5196,
     NORMAL,
     {
             [ARG_0] = {"pid", 4}, [ARG_1] = {"len", 4},
             [ARG_2] = {"user_mask_ptr", 8},
     }},
    {"sched_getattr",
      5310,
     NORMAL,
     {
             [ARG_0] = {"pid", 4}, [ARG_1] = {"uattr", 8},
             [ARG_2] = {"size", 4}, [ARG_3] = {"flags", 4},
     }},
    {"sched_getparam",
      5140,
     NORMAL,
     {
             [ARG_0] = {"pid", 4}, [ARG_1] = {"param", 8},
     }},
    {"sched_get_priority_max",
      5143,
     NORMAL,
     {
             [ARG_0] = {"policy", 4},
     }},
    {"sched_get_priority_min",
      5144,
     NORMAL,
     {
             [ARG_0] = {"policy", 4},
     }},
    {"sched_getscheduler",
      5142,
     NORMAL,
     {
             [ARG_0] = {"pid", 4},
     }},
    {"sched_rr_get_interval",
      5145,
     NORMAL,
     {
             [ARG_0] = {"pid", 4}, [ARG_1] = {"interval", 8},
     }},
    {"sched_setaffinity",
      5195,
     NORMAL,
     {
             [ARG_0] = {"pid", 4}, [ARG_1] = {"len", 4},
             [ARG_2] = {"user_mask_ptr", 8},
     }},
    {"sched_setattr",
      5309,
     NORMAL,
     {
             [ARG_0] = {"pid", 4}, [ARG_1] = {"uattr", 8},
             [ARG_2] = {"flags", 4},
     }},
    {"sched_setparam",
      5139,
     NORMAL,
     {
             [ARG_0] = {"pid", 4}, [ARG_1] = {"param", 8},
     }},
    {"sched_setscheduler",
      5141,
     NORMAL,
     {
             [ARG_0] = {"pid", 4}, [ARG_1] = {"policy", 4},
             [ARG_2] = {"param", 8},
     }},
    {"sched_yield", 124, NORMAL, {}},
    {"seccomp",
     277,
     NORMAL,
     {
             [ARG_0] = {"op", 4}, [ARG_1] = {"flags", 4},
             [ARG_2] = {"uargs", 8},
     }},
    {"semctl",
      5064,
     NORMAL,
     {
             [ARG_0] = {"semid", 4}, [ARG_1] = {"semnum", 4},
             [ARG_2] = {"cmd", 4}, [ARG_3] = {"arg", 8},
     }},
    {"semget",
      5062,
     NORMAL,
     {
             [ARG_0] = {"key", 4}, [ARG_1] = {"nsems", 4},
             [ARG_2] = {"semflg", 4},
     }},
    {"semop",
      5063,
     NORMAL,
     {
             [ARG_0] = {"semid", 4}, [ARG_1] = {"tsops", 8},
             [ARG_2] = {"nsops", 4},
     }},
    {"semtimedop",
      5214,
     NORMAL,
     {
             [ARG_0] = {"semid", 4}, [ARG_1] = {"tsops", 8},
             [ARG_2] = {"nsops", 4}, [ARG_3] = {"timeout", 8},
     }},
    {"sendfile",
     71,
     NORMAL,
     {
             [ARG_0] = {"out_fd", 4}, [ARG_1] = {"in_fd", 4},
             [ARG_2] = {"offset", 8}, [ARG_3] = {"count", 8},
     }},
    {"sendmmsg",
      5302,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"mmsg", 8}, [ARG_2] = {"vlen", 4},
             [ARG_3] = {"flags", 4},
     }},
    {"sendmsg",
      5045,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"msg", 8}, [ARG_2] = {"flags", 4},
     }},
    {"sendto",
      5043,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"buff", 8}, [ARG_2] = {"len", 8},
             [ARG_3] = {"flags", 4}, [ARG_4] = {"addr", 8},
             [ARG_5] = {"addr_len", 4},
     }},
    {"setdomainname",
      5166,
     NORMAL,
     {
             [ARG_0] = {"name", 8}, [ARG_1] = {"len", 4},
     }},
    {"setfsgid",
      5121,
     NORMAL,
     {
             [ARG_0] = {"gid", 4},
     }},
    {"setfsuid",
      5120,
     NORMAL,
     {
             [ARG_0] = {"uid", 4},
     }},
    {"setgid",
      5104,
     NORMAL,
     {
             [ARG_0] = {"gid", 4},
     }},
    {"setgroups",
      5114,
     NORMAL,
     {
             [ARG_0] = {"gidsetsize", 4}, [ARG_1] = {"grouplist", 8},
     }},
    {"sethostname",
      5165,
     NORMAL,
     {
             [ARG_0] = {"name", 8}, [ARG_1] = {"len", 4},
     }},
    {"setitimer",
      5036,
     NORMAL,
     {
             [ARG_0] = {"which", 4}, [ARG_1] = {"value", 8},
             [ARG_2] = {"ovalue", 8},
     }},
    {"set_mempolicy",
      5229,
     NORMAL,
     {
             [ARG_0] = {"mode", 4}, [ARG_1] = {"nmask", 8},
             [ARG_2] = {"maxnode", 8},
     }},
    {"setns",
      5303,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"nstype", 4},
     }},
    {"setpgid",
      5107,
     NORMAL,
     {
             [ARG_0] = {"pid", 4}, [ARG_1] = {"pgid", 4},
     }},
    {"setpriority",
      5138,
     NORMAL,
     {
             [ARG_0] = {"which", 4}, [ARG_1] = {"who", 4},
             [ARG_2] = {"niceval", 4},
     }},
    {"setregid",
      5112,
     NORMAL,
     {
             [ARG_0] = {"rgid", 4}, [ARG_1] = {"egid", 4},
     }},
    {"setresgid",
      5117,
     NORMAL,
     {
             [ARG_0] = {"rgid", 4}, [ARG_1] = {"egid", 4},
             [ARG_2] = {"sgid", 4},
     }},
    {"setresuid",
      5115,
     NORMAL,
     {
             [ARG_0] = {"ruid", 4}, [ARG_1] = {"euid", 4},
             [ARG_2] = {"suid", 4},
     }},
    {"setreuid",
      5111,
     NORMAL,
     {
             [ARG_0] = {"ruid", 4}, [ARG_1] = {"euid", 4},
     }},
    {"setrlimit",
      5155,
     NORMAL,
     {
             [ARG_0] = {"resource", 4}, [ARG_1] = {"rlim", 8},
     }},
    {"set_robust_list",
      5268,
     NORMAL,
     {
             [ARG_0] = {"head", 8}, [ARG_1] = {"len", 8},
     }},
    {"setsid", 157, NORMAL, {}},
    {"setsockopt",
     208,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"level", 4},
             [ARG_2] = {"optname", 4}, [ARG_3] = {"optval", 8},
             [ARG_4] = {"optlen", 4},
     }},
    {"set_tid_address",
      5212,
     NORMAL,
     {
             [ARG_0] = {"tidptr", 8},
     }},
    {"settimeofday",
      5159,
     NORMAL,
     {
             [ARG_0] = {"tv", 8}, [ARG_1] = {"tz", 8},
     }},
    {"setuid",
      5103,
     NORMAL,
     {
             [ARG_0] = {"uid", 4},
     }},
    {"setxattr",
      5180,
     NORMAL,
     {
             [ARG_0] = {"pathname", 8}, [ARG_1] = {"name", 8},
             [ARG_2] = {"value", 8}, [ARG_3] = {"size", 8},
             [ARG_4] = {"flags", 4},
     }},
    {"shmat",
      5029,
     NORMAL,
     {
             [ARG_0] = {"shmid", 4}, [ARG_1] = {"shmaddr", 8},
             [ARG_2] = {"shmflg", 4},
     }},
    {"shmctl",
      5030,
     NORMAL,
     {
             [ARG_0] = {"shmid", 4}, [ARG_1] = {"cmd", 4}, [ARG_2] = {"buf", 8},
     }},
    {"shmdt",
      5065,
     NORMAL,
     {
             [ARG_0] = {"shmaddr", 8},
     }},
    {"shmget",
      5028,
     NORMAL,
     {
             [ARG_0] = {"key", 4}, [ARG_1] = {"size", 8},
             [ARG_2] = {"shmflg", 4},
     }},
    {"shutdown",
      5047,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"how", 4},
     }},
    {"sigaltstack",
      5129,
     NORMAL,
     {
             [ARG_0] = {"uss", 8}, [ARG_1] = {"uoss", 8},
     }},
    {"signalfd4",
      5283,
     NORMAL,
     {
             [ARG_0] = {"ufd", 4}, [ARG_1] = {"user_mask", 8},
             [ARG_2] = {"sizemask", 8}, [ARG_3] = {"flags", 4},
     }},
    {"socket",
      5040,
     NORMAL,
     {
             [ARG_0] = {"family", 4}, [ARG_1] = {"type", 4},
             [ARG_2] = {"protocol", 4},
     }},
    {"socketpair",
      5052,
     NORMAL,
     {
             [ARG_0] = {"family", 4}, [ARG_1] = {"type", 4},
             [ARG_2] = {"protocol", 4}, [ARG_3] = {"usockvec", 8},
     }},
    {"splice",
      5263,
     NORMAL,
     {
             [ARG_0] = {"fd_in", 4}, [ARG_1] = {"off_in", 8},
             [ARG_2] = {"fd_out", 4}, [ARG_3] = {"off_out", 8},
             [ARG_4] = {"len", 8}, [ARG_5] = {"flags", 4},
     }},
    {"statfs",
      5134,
     NORMAL,
     {
             [ARG_0] = {"pathname", 8}, [ARG_1] = {"buf", 8},
     }},
    {"swapoff",
      5163,
     NORMAL,
     {
             [ARG_0] = {"specialfile", 8},
     }},
    {"swapon",
      5162,
     NORMAL,
     {
             [ARG_0] = {"specialfile", 8}, [ARG_1] = {"swap_flags", 4},
     }},
    {"symlinkat",
      5256,
     NORMAL,
     {
             [ARG_0] = {"oldname", 8}, [ARG_1] = {"newdfd", 4},
             [ARG_2] = {"newname", 8},
     }},
    {"sync", 81, NORMAL, {}},
    {"sync_file_range2",
     84,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"offset", 8},
             [ARG_2] = {"nbytes", 8}, [ARG_3] = {"flags", 4},
     }},
    {"syncfs",
      5301,
     NORMAL,
     {
             [ARG_0] = {"fd", 4},
     }},
    {"sysinfo",
      5097,
     NORMAL,
     {
             [ARG_0] = {"info", 8},
     }},
    {"syslog",
      5101,
     NORMAL,
     {
             [ARG_0] = {"type", 4}, [ARG_1] = {"buf", 8}, [ARG_2] = {"len", 4},
     }},
    {"tee",
      5265,
     NORMAL,
     {
             [ARG_0] = {"fdin", 4}, [ARG_1] = {"fdout", 4},
             [ARG_2] = {"len", 8}, [ARG_3] = {"flags", 4},
     }},
    {"tgkill",
      5225,
     NORMAL,
     {
             [ARG_0] = {"tgid", 4}, [ARG_1] = {"pid", 4}, [ARG_2] = {"sig", 4},
     }},
    {"timer_create",
      5216,
     NORMAL,
     {
             [ARG_0] = {"which_clock", 4}, [ARG_1] = {"timer_event_spec", 8},
             [ARG_2] = {"created_timer_id", 8},
     }},
    {"timer_delete",
      5220,
     NORMAL,
     {
             [ARG_0] = {"timer_id", 4},
     }},
    {"timerfd_create",
      5280,
     NORMAL,
     {
             [ARG_0] = {"clockid", 4}, [ARG_1] = {"flags", 4},
     }},
    {"timerfd_gettime",
      5281,
     NORMAL,
     {
             [ARG_0] = {"ufd", 4}, [ARG_1] = {"otmr", 8},
     }},
    {"timerfd_settime",
      5282,
     NORMAL,
     {
             [ARG_0] = {"ufd", 4}, [ARG_1] = {"flags", 4},
             [ARG_2] = {"utmr", 8}, [ARG_3] = {"otmr", 8},
     }},
    {"timer_getoverrun",
      5219,
     NORMAL,
     {
             [ARG_0] = {"timer_id", 4},
     }},
    {"timer_gettime",
      5218,
     NORMAL,
     {
             [ARG_0] = {"timer_id", 4}, [ARG_1] = {"setting", 8},
     }},
    {"timer_settime",
      5217,
     NORMAL,
     {
             [ARG_0] = {"timer_id", 4}, [ARG_1] = {"flags", 4},
             [ARG_2] = {"new_setting", 8}, [ARG_3] = {"old_setting", 8},
     }},
    {"times",
      5098,
     NORMAL,
     {
             [ARG_0] = {"tbuf", 8},
     }},
    {"tkill",
      5192,
     NORMAL,
     {
             [ARG_0] = {"pid", 4}, [ARG_1] = {"sig", 4},
     }},
    {"truncate",
      5074,
     NORMAL,
     {
             [ARG_0] = {"path", 8}, [ARG_1] = {"length", 8},
     }},
    {"umask",
      5093,
     NORMAL,
     {
             [ARG_0] = {"mask", 4},
     }},
    {"unlinkat",
      5253,
     NORMAL,
     {
             [ARG_0] = {"dfd", 4}, [ARG_1] = {"pathname", 8},
             [ARG_2] = {"flag", 4},
     }},
    {"unshare",
      5262,
     NORMAL,
     {
             [ARG_0] = {"unshare_flags", 8},
     }},
    {"userfaultfd",
      5317,
     NORMAL,
     {
             [ARG_0] = {"flags", 4},
     }},
    {"utimensat",
      5275,
     NORMAL,
     {
             [ARG_0] = {"dfd", 4}, [ARG_1] = {"filename", 8},
             [ARG_2] = {"utimes", 8}, [ARG_3] = {"flags", 4},
     }},
    {"vhangup", 58, NORMAL, {}},
    {"vmsplice",
      5266,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"iov", 8},
             [ARG_2] = {"nr_segs", 8}, [ARG_3] = {"flags", 4},
     }},
    {"wait4",
      5059,
     NORMAL,
     {
             [ARG_0] = {"upid", 4}, [ARG_1] = {"stat_addr", 8},
             [ARG_2] = {"options", 4}, [ARG_3] = {"ru", 8},
     }},
    {"waitid",
      5237,
     NORMAL,
     {
             [ARG_0] = {"which", 4}, [ARG_1] = {"upid", 4},
             [ARG_2] = {"infop", 8}, [ARG_3] = {"options", 4},
             [ARG_4] = {"ru", 8},
     }},
    {"write",
      5001,
     NORMAL,
     {
             [ARG_0] = {"fd", 4}, [ARG_1] = {"buf", 8}, [ARG_2] = {"count", 8},
     }},
    {"writev",
      5019,
     NORMAL,
     {
             [ARG_0] = {"fd", 8}, [ARG_1] = {"vec", 8}, [ARG_2] = {"vlen", 8},
     }},
};

const size_t mips64_syscall_list_size =
    sizeof(mips64_syscall_list) / sizeof(mips64_syscall_list[0]);
//List of syscalls that are not found in the template
//_newselect
//_sysctl
//access
//afs_syscall
//alarm
//cachectl
//cacheflush
//chmod
//chown
//copy_file_range
//creat
//create_module
//dup2
//epoll_create
//epoll_wait
//eventfd
//fork
//fremovexattr
//fstat
//futimesat
//get_kernel_syms
//getdents
//getegid
//geteuid
//getgid
//getgroups
//getpgrp
//getpid
//getpmsg
//getppid
//getpriority
//gettid
//gettimeofday
//getuid
//getxattr
//inotify_init
//inotify_init1
//lchown
//link
//lstat
//mkdir
//mknod
//munlockall
//munmap
//open
//pause
//perf_event_open
//pipe
//pkey_alloc
//pkey_free
//pkey_mprotect
//poll
//preadv2
//putpmsg
//pwritev2
//query_module
//readlink
//rename
//restart_syscall
//rmdir
//rt_sigreturn
//rt_sigsuspend
//sched_yield
//seccomp
//sendfile
//set_thread_area
//setsid
//setsockopt
//signalfd
//stat
//statx
//symlink
//sync
//sync_file_range
//sysfs
//sysmips
//timerfd
//umount2
//uname
//unlink
//ustat
//utime
//utimes
//vhangup
//vserver
