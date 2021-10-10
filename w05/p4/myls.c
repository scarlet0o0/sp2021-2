#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc,char *argv[]){
	DIR *dp1;
	DIR *dp2;
	struct dirent *dent;
	struct stat sbuf;
	char path[BUFSIZ];
	
	struct stat buf;
	if((dp1 = opendir(".")) == NULL){
		perror("opendir: HallymIniv");
		exit(1);
	}
	if((dp2 = opendir(".")) == NULL){
		perror("opendir: HallymIniv");
		exit(1);
	}

	
	printf("<Regular Files>\n");
	while((dent = readdir(dp1))){
		if(dent->d_name[0] == '.') continue;
		else{
			stat(dent->d_name,&buf);
			if(S_ISREG(buf.st_mode)){
		       		printf("Name : %s\n", dent->d_name);
			}
		}

	}
	
	printf("\n");	
	printf("<Directories>\n");
	while((dent = readdir(dp2))){
		if(dent->d_name[0] == '.') continue;
		else{
			stat(dent->d_name,&buf);
			if(S_ISDIR(buf.st_mode)){
		       		printf("Name : %s\n", dent->d_name);
			}
		}

	}

	
	closedir(dp1);
	closedir(dp2);

	return 0;
}
