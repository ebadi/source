# WHAT IS IT?
Kafel is a language and library for specifying syscall filtering policies.
The policies are compiled into BPF code that can be used with seccomp-filter.

This is NOT an official Google product.

# Usage

## With verbose error reporting
```c
struct sock_fprog prog;
kafel_ctxt_t ctxt = kafel_ctxt_create();
kafel_set_input_string(ctxt, seccomp_policy);
if (kafel_compile(ctxt, &prog)) {
  fprintf(stderr, "policy compilation failed: %s", kafel_error_msg(ctxt));
  kafel_ctxt_destroy(&ctxt);
  exit(-1);
}
kafel_ctxt_destroy(&ctxt);
prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog, 0, 0);
free(prog.filter);
```

## Without verbose error reporting
```c
struct sock_fprog prog;
if (kafel_compile_string(seccomp_policy, &prog)) {
  fputs("policy compilation failed", stderr);
  exit(-1);
}
prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog, 0, 0);
free(prog.filter);
```

# Policy language

A simple language is used to define policies.

A policy file has 3 parts:
 1. Constant definitions (optional)
 2. Policy definitions
 3. Top level policy declaration

## Numbers

Kafel supports following number notations:
 * Decimal `42`
 * Hexadecimal `0xfa1`
 * Octal `0777`
 * Binary `0b10101`

## Constant definitions

You may define numeric constants at the beging of policy file to make it more
readable.
The defined constants can then be used anywhere where a number is expected.

```
#define MYCONST 123
```

## Policy definitions

Policy definition is a list of action blocks and use statements separated by
commas.

__samples/__ contains some example policies that demonstrate supported features.

### Use statements

A `USE someOtherPolicy` behaves as if `someOtherPolicy` body was pasted in its
place. You may only use policies defined before the use statement.

With use statements you can create meaningful groups of filtering rules that are
building blocks of bigger policies.

### Action blocks

Action block consist of a target and list of syscall matching rules separated
with commas.

Target of first rule matched is the policy decision.

Following table list Kafel targets and their corresponding seccomp-filter
return values.

Kafel           | seccomp-filter
--------------- | ---------------------------
`ALLOW`         | `SECCOMP_RET_ALLOW`
`KILL`, `DENY`  | `SECCOMP_RET_KILL`
`ERRNO(number)` | `SECCOMP_RET_ERRNO+number`
`TRAP(number)`  | `SECCOMP_RET_TRAP+number`
`TRACE(number)` | `SECCOMP_RET_TRACE+number`

### Syscall matching rules

A rules consist of syscall name and optional list of boolean expressions.

List of boolean expressions separated by commas.
A comma is semantically equivalent to `||` but has the lowest precedence,
therefore it may be easier to read.

#### Syscall naming

Normally syscalls are specified by their names as defined in Linux kernel.
However, you may also filter __custom syscalls__ that are not in the standard
syscall list.
You can either define a constant and use it in place of syscall name or
utilize `SYSCALL` keyword.

```
#define mysyscall -1

POLICY my_const {
  ALLOW {
    mysyscall
  }
}

POLICY my_literal {
  ALLOW {
    SYSCALL[-1]
  }
}
```

#### Argument filtering

Boolean expressions are used to filter syscalls based on their arguments.
A expression resembles C language syntax, except that there are no
arithmetic operators.

```
some_syscall(first_arg, my_arg_name) { first_arg == 42 && my_arg_name != 42 }
```

Bitwise and (`&`) operator can be used to test for flags.

```
mmap { (prot & PROT_EXEC) == 0 }
```

You don't have to declare arguments for well-known syscalls but can just use
their regular names as specified in Linux kernel and `man` pages.

```
write { fd == 1 }
```

## Top level policy declaration

```
USE topLevel DEFAULT the_action
```

Specifies that `topLevel` policy is compiled and action `the_action` should be
taken when no rule matches.

# Example

When used with [nsjail](https://github.com/google/nsjail), the following command allows to create a fairly constrained environment for your shell

```
$ ./nsjail --chroot / --seccomp_string 'POLICY a { ALLOW { write, execve, brk, access, mmap, open, newfstat, close, read, mprotect, arch_prctl, munmap, getuid, getgid, getpid, rt_sigaction, geteuid, getppid, getcwd, getegid, ioctl, fcntl, newstat, clone, wait4, rt_sigreturn, exit_group } } USE a DEFAULT KILL' -- /bin/sh -i
```
```
[2017-01-15T21:53:08+0100] Mode: STANDALONE_ONCE
[2017-01-15T21:53:08+0100] Jail parameters: hostname:'NSJAIL', chroot:'/', process:'/bin/sh', bind:[::]:0, max_conns_per_ip:0, uid:(ns:1000, global:1000), gid:(ns:1000, global:1000), time_limit:0, personality:0, daemonize:false, clone_newnet:true, clone_newuser:true, clone_newns:true, clone_newpid:true, clone_newipc:true, clonew_newuts:true, clone_newcgroup:false, keep_caps:false, tmpfs_size:4194304, disable_no_new_privs:false, pivot_root_only:false
[2017-01-15T21:53:08+0100] Mount point: src:'/' dst:'/' type:'' flags:0x5001 options:''
[2017-01-15T21:53:08+0100] Mount point: src:'(null)' dst:'/proc' type:'proc' flags:0x0 options:''
[2017-01-15T21:53:08+0100] PID: 18873 about to execute '/bin/sh' for [STANDALONE_MODE]
/bin/sh: 0: can't access tty; job control turned off
$ set
IFS='
'
OPTIND='1'
PATH='/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin'
PPID='0'
PS1='$ '
PS2='> '
PS4='+ '
PWD='/'
$ id
Bad system call
$ exit
[2017-01-15T21:53:17+0100] PID: 18873 exited with status: 159, (PIDs left: 0)
```
