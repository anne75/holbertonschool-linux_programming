#include "func_header.h"
#include "syscalls.h"

/**
 * action - print the syscall number
 * @regs: struct holding information collected by ptrace
 */
void action(user_regs_t *regs)
{
	size_t arr_len, i;

	arr_len = sizeof(syscalls_64_g) / sizeof(syscalls_64_g[0]);
	for (i = 0; i < arr_len; ++i)
	{
		if (syscalls_64_g[i].nr == regs->orig_rax)
		{
			printf("%s\n", syscalls_64_g[i].name);
			break;
		}
	}
}


/**
 * main - entrypoint
 * @ac: number of command line arguments
 * @av: array of command line arguments
 * @env: environment
 * Return: 0 on success
 */
int main(int ac, char **av, char **env)
{
	int ret_value;

	setbuf(stdout, NULL);
	if (ac < 2)
	{
		puts("./strace_1 command [args...]");
		return (1);
	}

	ret_value = run_ptrace(av, env, &action);

	return (ret_value);
}
