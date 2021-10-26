#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SLEEP_SEC 5

int main(int argc, char* argv[]){
	if(argc != 2) exit(EXIT_SUCCESS);
	int sleepTime = atoi(argv[1]);
	sleep(sleepTime);
	return 0;
}

