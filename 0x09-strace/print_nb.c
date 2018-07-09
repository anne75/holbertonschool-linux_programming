#include "func_header.h"


void action(user_regs_t *regs)
{
	printf("%lu\n", regs->orig_rax);
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

	ret_value = run_ptrace(ac, av, env, &action);

	return (ret_value);
}
