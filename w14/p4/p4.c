#include <unistd.h>
#include <signal.h>
//#include <siginfo.h>
#include <stdio.h>

void handler(int signo)
{
	sigset_t set;

	sigfillset(&set);
	sigdelset(&set,SIGINT);
	sigprocmask(SIG_BLOCK,&set,(sigset_t *)NULL);

	psignal(signo,"At handler : Wake up!");
}


int main(void)
{

	signal(SIGALRM,handler);
	sigset_t set;

	sigfillset(&set);
		sigdelset(&set,SIGALRM);
	sigdelset(&set,SIGINT);
	sigprocmask(SIG_BLOCK,&set,(sigset_t *)NULL);

	for(int i = 0; i < 5; i++)
	{
		alarm(2);
		printf("Pause...\n");
		pause();
	}

	printf("Bye~\n");
	return 0;
}
