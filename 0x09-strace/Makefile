
CC=gcc-4.8
FLAGS=-Wall -pedantic -Werror -Wextra

strace_0: ptrace_syscall.c print_nb.c func_header.h
	$(CC) $(FLAGS) ptrace_syscall.c print_nb.c -o $@

strace_1: ptrace_syscall.c print_syscall.c func_header.h syscalls.h
	$(CC) $(FLAGS) ptrace_syscall.c print_syscall.c -o $@

strace_2: ptrace_syscall.c print_syscall_return.c func_header.h syscalls.h
	$(CC) $(FLAGS) ptrace_syscall.c print_syscall_return.c -o $@
