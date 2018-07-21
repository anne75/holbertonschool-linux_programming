#include "func_header.h"
#include "syscalls.h"

/**
 * pre_action - print the syscall number
 * @regs: struct holding information collected by ptrace
 */
void pre_action(user_regs_t *regs)
{
	size_t arr_len, i;

	arr_len = sizeof(syscalls_64_g) / sizeof(syscalls_64_g[0]);
	for (i = 0; i < arr_len; ++i)
	{
		if (syscalls_64_g[i].nr == regs->orig_rax)
		{
			printf("%s", syscalls_64_g[i].name);
			break;
		}
	}
	/* exit_group is only seen on entry */
	if (regs->orig_rax == 231)
		putchar('\n');
}

/**
 * post_action - print new line
 * @regs: struct holding information collected by ptrace
 */
void post_action(user_regs_t *regs)
{
	/* execve is only seen on return */
	if (regs->orig_rax == 59)
		printf("%s", syscalls_64_g[regs->orig_rax].name);
	putchar('\n');
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

	ret_value = run_ptrace(av, env, &pre_action, &post_action);
	return (ret_value);
}
