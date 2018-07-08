#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>

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

int main(int ac, char **av, char **env)
{
	pid_t pid, my_pid;
	int status;
/*	struct user_regs_s regs;*/
	long value;

	if (ac < 2)
	{
		puts("usage: process_to_trace");
		return (1);
	}

	pid = fork();
	if (pid == 0)
	{
		/* child process */
		my_pid = getpid();
		ptrace(PTRACE_TRACEME, my_pid, NULL, NULL);
		/*kill(getpid(), SIGSTOP);*/
		execve(av[1], av + 1, env);
		perror("execve");
	}
	else if (pid > 0)
	{
		/* parent process */
		while (1)
		{
			waitpid(pid, &status, __WALL);
			if (WIFEXITED(status))
				break;
			printf("Stopped? %d\n", WIFSTOPPED(status));
			printf("In a syscall? %d\n", WSTOPSIG(status) == SIGTRAP);
			errno = 0;
			/*value = ptrace(PTRACE_GETREGS, pid, NULL, (void *) &regs); -> this version segfaults ls*/
			value = ptrace(PTRACE_PEEKUSER, pid, 15 * 8, NULL);
			if (value == -1 && errno)
				perror("ptrace getregs");
			else
				printf("syscall %ld\n", value /*regs.orig_rax*/);
			/* tracee uses syscall */
			/* why does it need to be here and not before */
			/* in both cases stopped and sigtrap but ptrace ESRCH*/
			ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
		}
		printf("Exit status: %d\n", WEXITSTATUS(status));
		puts("segfault ?");
	}
	else
	{
		puts("error during fork");
	}
	printf("exit for pid %d\n", pid);
	return (0);
}
