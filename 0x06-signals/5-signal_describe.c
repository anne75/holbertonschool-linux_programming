#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * main - entrypoint to describe a signal.
 * @ac: number of arguments passed, should be one
 * @av: array holding the arguments as strings.
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int ac, char **av)
{
	int signb;

	if (ac != 2)
	{
		printf("Usage: %s <signum>\n", av[0]);
		return (EXIT_FAILURE);
	}

	signb = atoi(av[1]);
	printf("%s: %s\n", av[1], strsignal(signb));
	return (EXIT_SUCCESS);
}
