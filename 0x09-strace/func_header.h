#ifndef _FUNC_HEADER_
#define _FUNC_HEADER_

#include <stdio.h>
#include <string.h>
#include <unistd.h>

/**
 * struct user_regs_s - strcut returned by ptrace getregs
 * @r15
 * @r14
 * @r13
 * @r12
 * @rbp
 * @rbx
 * @r11
 * @r10
 * @r9
 * @r8
 * assumes 8 byts long
 * from linux x86 sys reg
 * sys user struc does not match
 * what I see
 */
typedef struct user_regs_s
{
	unsigned long int r15; /* 0 */
	unsigned long int r14; /* 1 */
	unsigned long int r13; /* 2 */
	unsigned long int r12; /* 3 */
	unsigned long int rbp; /* 4 */
	unsigned long int rbx; /* 5 */
	unsigned long int r11; /* 6 */
	unsigned long int r10; /* 7 */
	unsigned long int r9;  /* 8 */
	unsigned long int r8;  /* 9 */
	unsigned long int rax; /* 10 */
	unsigned long int rcx; /* 11 */
	unsigned long int rdx; /* 12 */
	unsigned long int rsi; /* 13 */
	unsigned long int rdi; /* 14 */
	unsigned long int orig_rax; /* 15 */
	unsigned long int rip;
	unsigned long int cs;
	unsigned long int eflags;
	unsigned long int rsp;
	unsigned long int ss;
	unsigned long int fs_base;
	unsigned long int gs_base;
	unsigned long int ds;
	unsigned long int es;
	unsigned long int fs;
	unsigned long int gs;
} user_regs_t;


/* ptrace_syscall.c */
void tracer(pid_t pid, void (*action)(user_regs_t *regs));
int run_ptrace(int ac, char **av, char **env,
	       void (*action)(user_regs_t *regs));

#endif
