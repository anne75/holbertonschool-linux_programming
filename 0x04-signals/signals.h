#ifndef _SIGNALS_H_
#define _SIGNALS_H_

#include <signal.h>

/*question 0*/
int handle_signal(void);

/*question 1*/
void (*current_handler_signal(void))(int);

/*question 2*/
int handle_sigaction(void);

/*question 3*/
void (*current_handler_sigaction(void))(int);

/*question 4*/
int trace_signal_sender(void);

/*question 10*/
int pid_exist(pid_t pid);

/*question 12 or 100*/
void all_in_one(void);

/*question 13 or 101*/
int sigset_init(sigset_t *set, int *signals);

/*question 14 or 102*/
int signals_block(int *signals);

/*question 15 or 103*/
int signals_unblock(int *signals);

/*question 16 or 104*/
int handle_pending(void (*handler)(int));

#endif
