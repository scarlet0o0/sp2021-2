#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(int argc ,char *argv[]){
	double random_num;
	double prob = atof(argv[1]);
	int status;
	pid_t pid;
	pid_t pid4wait;
	srand(time(NULL));
	
	printf("Prob = %f\n",prob);
	while((random_num= rand()/(RAND_MAX*1.0)) <= prob){
		pid = fork();
		printf("My PID (%d), My Parent PID (%d)\n",getpid(),getppid());
		if(pid > 0){
			pid4wait = wait(&status);
			printf("Waited pid: %d\n",pid4wait);
		}
	}

	return 0;
}

