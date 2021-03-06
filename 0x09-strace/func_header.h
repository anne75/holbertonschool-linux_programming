#ifndef _FUNC_HEADER_
#define _FUNC_HEADER_

#include <stdio.h>
#include <string.h>
#include <unistd.h>

/**
 * struct user_regs_s - strcut returned by ptrace getregs
 * @r15: register
 * @r14: register
 * @r13: register
 * @r12: register
 * @rbp: register
 * @rbx: register
 * @r11: register
 * @r10: register
 * @r9: register
 * @r8: register
 * @rax: register
 * @rcx: register
 * @rdx: register
 * @rsi: register
 * @rdi: register
 * @orig_rax: register entering function
 * @rip: register
 * @cs: ??
 * @eflags: ??
 * @rsp: register
 * @ss: ??
 * @fs_base: ??
 * @gs_base: ??
 * @ds: ??
 * @es: ??
 * @fs: ??
 * @gs: ??
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
void tracer(pid_t pid, void (*pre_action)(user_regs_t *regs),
	    void (*post_action)(user_regs_t *regs));
int run_ptrace(char **av, char **env,
	       void (*pre_action)(user_regs_t *regs),
	       void (*post_action)(user_regs_t *regs));

#endif
