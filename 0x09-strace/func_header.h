#ifndef _FUNC_HEADER_
#define _FUNC_HEADER_

#include <stdio.h>
#include <string.h>
#include <unistd.h>

/**
 * assumes 8 byts long
 * from linux x86 sys reg
 * sys user struc does not match
 * what I see
 */
struct user_regs_s
{
	long int r15; /* 0 */
	long int r14; /* 1 */
	long int r13; /* 2 */
	long int r12; /* 3 */
	long int rbp; /* 4 */
	long int rbx; /* 5 */
	long int r11; /* 6 */
	long int r10; /* 7 */
	long int r9;  /* 8 */
	long int r8;  /* 9 */
	long int rax; /* 10 */
	long int rcx; /* 11 */
	long int rdx; /* 12 */
	long int rsi; /* 13 */
	long int rdi; /* 14 */
	long int orig_rax; /* 15 */
	long int rip;
	long int cs;
	long int eflags;
	long int rsp;
};


/* ptrace_syscall.c */
void tracer(pid_t pid, void (*action)(long int value));
int run_ptrace(int ac, char **av, char **env, void (*action)(long int value));

#endif
