#include <stdio.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int ac, char **av, char **env)
{
	pid_t pid, my_pid;
	int status;

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
	}
	else if (pid > 0)
	{
		/* parent process */
		waitpid(pid, &status, WNOHANG);
		while (!WIFEXITED(status))
		{
			/* tracee uses syscall */
			ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
			printf("syscall ->");
			/* get syscall return */
			ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
			puts(" return");
			waitpid(pid, &status, WNOHANG);
		}
		printf("%d\n", WEXITSTATUS(status));
	}
	else
	{
		puts("error during fork");
	}
	return (0);
}
