#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig, struct __siginfo * sig_info, void * v) {
    if (sig == SIGUSR1)
        printf("SIGUSR1");
    if (sig == SIGUSR2)
        printf("SIGUSR2");
	printf(" from %d\n", sig_info->si_pid);
}

int main() {
	struct sigaction sig_act;

	sig_act.sa_sigaction = &handler;
	sigaction(SIGUSR1, &sig_act, NULL);
	sigaction(SIGUSR2, &sig_act, NULL);

	if (sleep(10) == 0)
        printf("No signals were caught\n");
	return 0;
}	
