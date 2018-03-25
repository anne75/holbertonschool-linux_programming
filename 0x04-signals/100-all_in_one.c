#include <signal.h>
#include <stdio.h>

/**
 * handle_all - print a message about the signal received.
 * @signb: signal number
 * @siginfo: struct holding signal information
 * @context: struct holding user context information
 */
void handle_all(int signb, siginfo_t *siginfo, void *context)
{
	char *s = "Caught";
	(void) signb;
	(void) context;

	psiginfo(siginfo, s);
}

/**
 * all_in_one - install one signal handler for all signals
 */
void all_in_one(void)
{
	int i;
	struct sigaction action;

	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = handle_all;
	for (i = 1; i < NSIG; ++i)
		sigaction(i, &action, NULL);
}
