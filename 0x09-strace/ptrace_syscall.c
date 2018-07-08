#include <errno.h>
#include <signal.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "func_header.h"


/**
 * run_ptrace - execute and trace a given command
 * @ac: number of command line arguments
 * @av: array of command line arguments
 * @env: environment
 * Return: 0 on success, 1 on failure
 */
int run_ptrace(int ac, char **av, char **env, void (*action)(long int value))
{
	pid_t pid, my_pid;

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
		execve(av[1], av + 1, env);
		perror("execve");
		return (1);
	}
	else if (pid > 0)
	{
		/* parent process */
		tracer(pid, action);
		puts("back from tracer");
	}
	else
	{
		fprintf(stderr, "error during fork");
		return (1);
	}
	puts("exit success ptrace");
	return (0);
}

/**
 * tracer - tracer actions.
 * @pid: pid of tracee
 */
void tracer(pid_t pid, void (*action)(long int value))
{
	int status, enter_syscall;
	long value;
	struct user_regs_s regs;

	/* the first syscall is execve which does not return */
	enter_syscall = -1;
	while (1)
	{
		waitpid(pid, &status, __WALL);
		if (WIFEXITED(status))
			break;
		if (!(WIFSTOPPED(status) &&
		      WSTOPSIG(status) == SIGTRAP))
		{
			continue;
		}
		else if (enter_syscall > 0)
		{
			enter_syscall = 0;
		}
		else
		{
/*15 is ORIG_RAX on my system with 8 bytes long */
			value = ptrace(PTRACE_PEEKUSER, pid, 15 * 8, NULL);
			if (!(value == -1 && errno))
			{
				enter_syscall += 1;
				action(value);
			}
			value = ptrace(PTRACE_GETREGS, pid, NULL, (void *) &regs);
			printf("regs %ld\n", regs.orig_rax);
		}
		ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
	}
	puts("exit tracer");
}
