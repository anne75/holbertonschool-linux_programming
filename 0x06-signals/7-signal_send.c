#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * main - sends SIGINT to a process passed in argument
 * @ac: number of arguments
 * @av: array of arguments
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int ac, char **av)
{
	int kill_r, pid;

	if (ac != 2)
	{
		printf("Usage: %s <pid>\n", av[0]);
		return (EXIT_FAILURE);
	}

	pid = atoi(av[1]);
	kill_r = kill(pid, SIGINT);
	if (!kill_r)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
