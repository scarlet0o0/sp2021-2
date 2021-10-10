#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	char *val;
	
	val = getenv(argv[1]);
	
	if(strstr(val,argv[2]) != NULL)
		printf("PATH has %s!!",argv[2]);
	else
		printf("PATH does not have %s",argv[2]);
	return 0;
}
