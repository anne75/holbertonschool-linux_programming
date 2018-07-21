#include "func_header.h"
#include "syscalls.h"

/**
 * get_syscall_t - get syscall type
 * @index: syscall number
 * Return: syscall type
 */
const syscall_t *get_syscall_t(size_t index)
{
	size_t arr_len, i;

	arr_len = sizeof(syscalls_64_g) / sizeof(syscalls_64_g[0]);
	for (i = 0; i < arr_len; ++i)
	{
		if (syscalls_64_g[i].nr == index)
		{
			return (syscalls_64_g + i);
		}
	}
	return (NULL);
}

/**
 * pre_action - print the syscall number
 * @regs: struct holding information collected by ptrace
 */
void pre_action(user_regs_t *regs)
{
	const syscall_t *syscall;

	syscall = get_syscall_t(regs->orig_rax);
	if (syscall)
		printf("%s = ", syscall->name);
	/* exit never returns here */
	if (regs->orig_rax == 231)
		printf("?\n");
}

/**
 * post_action - print new line
 * @regs: struct holding information collected by ptrace
 */
void post_action(user_regs_t *regs)
{
	const syscall_t *syscall;

	syscall = get_syscall_t(regs->orig_rax);
	/* execve is only seen on return */
	if (regs->orig_rax == 59)
		printf("%s = ", syscall->name);
	switch (syscall->ret)
	{
	case SSIZE_T :
	case INT :
		printf("%ld\n", regs->rax);
		break;
	case VOID_P :
	default :
		printf("%p\n", (void *)regs->rax);
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

	ret_value = run_ptrace(av, env, &pre_action, &post_action);
	return (ret_value);
}
