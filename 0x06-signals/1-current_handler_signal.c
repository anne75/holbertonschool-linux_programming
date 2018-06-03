#include <signal.h>
#include <stdio.h>

/**
 * current_handler_signal - return the current sighandler for SIGINT
 *
 * Return: pointer to sighandler function on succes, NULL on error.
 */
void (*current_handler_signal(void))(int)
{
	void (*handler)(int);

	handler = signal(SIGINT, SIG_DFL);
	if (handler == SIG_ERR)
		return (NULL);
	if (signal(SIGINT, handler) == SIG_ERR)
		return (NULL);

	return (handler);
}
