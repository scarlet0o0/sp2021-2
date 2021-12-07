#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<string.h>

int main(void){
	sigset_t new;

	sigemptyset(&new);
	sigaddset(&new,SIGINT);
	sigprocmask(SIG_BLOCK, &new,(sigset_t *)NULL);

	//sighold(SIGINT);
	
	for(int n = 0; n < 10; n++)
	{
		printf("Hallym SOftware\n");
		sleep(1);
	}

	return 0;
}
