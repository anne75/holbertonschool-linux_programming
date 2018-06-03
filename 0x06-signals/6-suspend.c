#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * sighandler - handles SIGINT signal.
 * @signb: signa number
 */
void sighandler(int signb)
{
	if (signb == SIGINT)
	{
		printf("Caught %d\n", signb);
		printf("Signal received\n");
	}
}

/**
 * main - program that waites on SIGINT.
 *
 * Return: EXIT_SUCCESS
 */
int main(void)
{
	signal(SIGINT, sighandler);
	pause();
	return (EXIT_SUCCESS);
}
