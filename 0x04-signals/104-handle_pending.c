#include <signal.h>
#include <unistd.h>


/**
 * handle_pending - sets a signal handler to all prending signals.
 * @handler: signal handler
 * Return: 0 on success, -1 on error.
 */
int handle_pending(void (*handler)(int))
{
	int check_ret, i;
	sigset_t pending_signals;
	struct sigaction action;

	if (!handler)
		return (-1);
	action.sa_handler = handler;
	check_ret = sigpending(&pending_signals);
	if (check_ret)
		return (-1);

	for (i = 1; i < NSIG; ++i)
	{
		if (sigismember(&pending_signals, i))
			if (sigaction(i, &action, NULL) == -1)
				return (-1);
	}
	return (0);
}
