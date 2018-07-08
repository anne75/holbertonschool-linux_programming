#ifndef _FUNC_HEADER_
#define _FUNC_HEADER_

#include <stdio.h>
#include <string.h>
#include <unistd.h>


/* ptrace_syscall.c */
void tracer(pid_t pid, void (*action)(long int value));
int run_ptrace(int ac, char **av, char **env, void (*action)(long int value));

#endif
