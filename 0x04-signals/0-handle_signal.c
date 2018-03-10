#include <signal.h>
#include <stdio.h>


/**
 * handle_sigint - signal handle
 * signb: signal number
 */
void handle_sigint(int signb)
{
	if (signb == SIGINT)
		printf("Gotcha! [%d]\n", signb);
}



/**
 * handle_signal - handles SIGINT by printing a message
 *
 * Return: 0 on success, 1 on failure.
 */
int handle_signal(void)
{

	if (signal(SIGINT, handle_sigint) == SIG_ERR)
		return (1);

	return (0);
}
