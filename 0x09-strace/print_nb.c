#include "func_header.h"

/**
 * pre_action - print the syscall number
 * @regs: struct holding information collected by ptrace
 */
void pre_action(user_regs_t *regs)
{
	printf("%lu\n", regs->orig_rax);
}

/**
 * post_action - print new line
 * @regs: struct holding information collected by ptrace
 */
void post_action(__attribute__((unused)) user_regs_t *regs)
{
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
		puts("./strace_0 command [args...]");
		return (1);
	}

	ret_value = run_ptrace(av, env, &pre_action, &post_action);

	return (ret_value);
}
