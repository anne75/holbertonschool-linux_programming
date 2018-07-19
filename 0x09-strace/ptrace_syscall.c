#include <errno.h>
#include <signal.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "func_header.h"


/**
 * run_ptrace - execute and trace a given command
 * @av: array of command line arguments
 * @env: environment
 * @action: function used by the tracer to get info about tracee
 * Return: 0 on success, 1 on failure
 */
int run_ptrace(char **av, char **env,
	       void (*action)(user_regs_t *regs))
{
	pid_t pid, my_pid;

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
	}
	else
	{
		fprintf(stderr, "error during fork");
		return (1);
	}
	return (0);
}

/**
 * tracer - tracer actions.
 * @pid: pid of tracee
 * @action: function to print information about tracee
 */
void tracer(pid_t pid, void (*action)(user_regs_t *regs))
{
	int status, enter_syscall;
	long value;
	user_regs_t regs;

	/* the first syscall is when execve returns successfully in tracee */
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
			value = ptrace(PTRACE_GETREGS, pid, NULL,
				       (void *) &regs);
			if (!(value == -1 && errno))
			{
				enter_syscall += 1;
				action(&regs);
			}
		}
		ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
	}
}
