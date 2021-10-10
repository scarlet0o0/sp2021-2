#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	
	if(rename(argv[1],argv[2]) == -1 ){
		perror("이름변경");
		exit(1);
	}	
	

	return 0;
}
