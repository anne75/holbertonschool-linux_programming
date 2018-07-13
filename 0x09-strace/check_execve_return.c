#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - function to test what excve returns
 * @ac: number of cla
 * @av: array of cla
 * Used to disassemble 2 syscalls and check execve return
 * value on success.
 * Return: 0 on success, 1 on error
 */
int main(int __attribute__((unused)) ac, char __attribute__((unused)) **av)
{
	pid_t pid;
        char *const array[2] = {"/bin/echo", "hello"};

	pid = fork();
	if (pid == 0)
	{
/* child */
		execve(array[0], &array[0], NULL);
	}
	else if (pid > 0)
/* parent */
	{
		wait(NULL);
		write(1, "Parent\n", 7);
	}
	else
	{
		return (1);
	}
	return (0);
}
