#include <signal.h>
#include <stdio.h>


/**
 * handle_sigquit - prints the sending process id on sigquit
 * @signb: signal number
 * @info: siginfo struct holding pid
 * @context: u_context struct
 */
void handle_sigquit(int signb, siginfo_t *info, void *context)
{
	(void) context;

	if (signb == SIGQUIT)
		printf("SIGQUIT sent by %d\n", info->si_pid);
}


/**
 * trace_signal_handler - prints the pid of process sending SIGQUIT
 *
 * Return: 0 on success, -1 on error
 */
int trace_signal_sender(void)
{
	struct sigaction action;
	int sigaction_r;

	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = handle_sigquit;
	sigaction_r = sigaction(SIGQUIT, &action, NULL);
	return (sigaction_r);
}
