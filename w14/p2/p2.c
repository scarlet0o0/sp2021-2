#include <unistd.h>
#include <signal.h>
//#include <siginfo.h>
#include <stdlib.h>
#include <stdio.h>

void handler(int signo)
{
	printf("SIGQUIT handler is called!");
}

int main(void){
	void (*hand)(int);

	hand = signal(SIGQUIT, handler);
	if(hand == SIG_ERR)
	{
		perror("signal");
		exit(1);
	}

	printf("Wait 1st Ctrl+/.....: SIGQUIT\n");
	pause();

	return 0;
}
