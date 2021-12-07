#include <signal.h>
#include <stdio.h>

int main(void)
{
	sigset_t st;

	//sigemptyset(&st);
	sigfillset(&st);

	//sigaddset(&st,SIGINT);
	//sigaddset(&st,SIGQUIT);

	if(sigismember(&st,SIGBUS))
		printf("SIGBUS is set \n");
	else
		printf("SIGBUS is not set");

	//printf("** Bit Pattern: %x\n",st.__sigbits[0]);

	return 0;
}
