#include <signal.h>
#include <errno.h>

/**
 * pid_exist - check if a process exists given a pid.
 * @pid: a process id
 * Return: 1 if process exists else 0.
 */
int pid_exist(pid_t pid)
{
	return (!kill(pid, 0) || errno != ESRCH);
}
