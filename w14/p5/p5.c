#include<unistd.h>
#include<signal.h>
//#include<siginfo.h>
#include<stdio.h>
#include<sys/time.h>
#include<stdlib.h>

void handler(int signo)
{	
	psignal(signo, "Nice to meet you!");
}

int main(void)
{
	struct itimerval it;

	sigset(SIGALRM,handler);
	it.it_value.tv_sec = 1;
	it.it_value.tv_usec = 0;
	it.it_interval.tv_sec = 1;
	it.it_interval.tv_usec = 0;
	
	if(setitimer(ITIMER_REAL,&it,(struct itimerval *)NULL) == -1){
		perror("setitimer");
		exit(1);
	}

	while(1)
	{
		if(getitimer(ITIMER_REAL, &it) == -1){
			perror("getitimer");
			exit(1);
		}
		
		sleep(1);
	}

	return 0;
}
