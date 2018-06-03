#include <signal.h>
#include <stdlib.h>

/**
 * signals_unblock - unblock a given set of signals
 * @signals: 0 terminated array of signal numbers.
 * Return: 0 on success, 1 on failure.
 */
int signals_unblock(int *signals)
{
	int check_ret, signb;
	sigset_t to_block;

	check_ret = sigemptyset(&to_block);
	if (check_ret)
		return (-1);

	while ((signb = *signals++) != 0)
	{
		check_ret = sigaddset(&to_block, signb);
		if (check_ret)
			return (-1);
	}
	check_ret = sigprocmask(SIG_UNBLOCK, &to_block, NULL);
	if (check_ret)
		return (-1);
	return (0);
}
