#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
int main(int argc ,char *argv[]){
	int fd;

	if(mkdir(argv[1],0755) ==-1){
		perror(argv[1]);
		exit(1);
	}
	
	char *cwd;
	char wd[BUFSIZ];

	cwd = getcwd(NULL,BUFSIZ);

	chdir(argv[1]);

	getcwd(wd,BUFSIZ);
	
	fd = open("README.TXT",O_RDWR|O_CREAT,0644);
	if(fd == -1){
		perror("Creat");
		exit(1);
	}

	close(fd);
	return 0;

}
