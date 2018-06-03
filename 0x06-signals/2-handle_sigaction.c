#include <signal.h>
#include <stdio.h>

/**
 * handle_sigint - signal handle
 * @signb: signal number
 */
void handle_sigint(int signb)
{
	if (signb == SIGINT)
		printf("Gotcha! [%d]\n", signb);
}

/**
 * handle_sigaction - create a sighandler for sigint
 *
 * Return: 0 on success, -1 on failure
 */
int handle_sigaction(void)
{
	int sigaction_r;
	struct sigaction new;

	new.sa_handler = handle_sigint;
	sigemptyset(&new.sa_mask);
	sigaction_r = sigaction(SIGINT, &new, NULL);
	return (sigaction_r);
}
