#include <signal.h>
#include <stdio.h>


/**
 * current_handler_sigaction - retrives SIGINT current handler
 *
 * Return: a Pointer to the sighandler on success, NULL otherwise.
 */
void (*current_handler_sigaction(void))(int)
{
	struct sigaction old;

	if (sigaction(SIGINT, NULL, &old) == -1)
		return (NULL);

	return (old.sa_handler);
}
