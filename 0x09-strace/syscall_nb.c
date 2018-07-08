#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>


/**
 * main - execute and trace a given command
 * @ac: number of command line arguments
 * @av: array of command line arguments
 * @env: environment
 * Return: 0 on success, 1 on failure
 */
int main(int ac, char **av, char **env)
{
	pid_t pid, my_pid;
	int status, enter_syscall;
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
		execve(av[1], av + 1, env);
		perror("execve");
		return (1);
	}
	else if (pid > 0)
	{
		/* parent process */
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
					printf("%ld\n", value);
				}
			}
			ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
		}
	}
	else
	{
		fprintf(stderr, "error during fork");
		return (1);
	}
	return (0);
}
