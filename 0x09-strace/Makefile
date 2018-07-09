
CC=gcc-4.8
FLAGS=-Wall -pedantic -Werror -Wextra

strace_0:
	$(CC) $(FLAGS) syscall_nb.c -o strace_0

strace_1:
	$(CC) $(FLAGS) ptrace_syscall.c print_syscall.c -o strace_1
