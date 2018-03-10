#include <signal.h>

/**
 * sigset_init - initializes a sigset
 * @set: a signal set
 * @signals: 0 terminated array of signals
 * Return: 0 on success, -1 on error
 */
int sigset_init(sigset_t *set, int *signals)
{
	int check_ret, signb;

	check_ret = sigemptyset(set);
	if (check_ret)
		return (-1);

	while((signb = *signals++) != 0)
	{
		check_ret = sigaddset(set, signb);
		if (check_ret)
			return (-1);
	}
	return (0);
}
