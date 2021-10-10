#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<getopt.h>

int main(int argc, char *argv[]){
	FILE *rfp, *wfp;
	int n,c;

	int option;
	int flag = 0;

	int argv_num1=1,argv_num2=2;
	while(( option = getopt(argc,argv,"d:")) != -1){
		switch(option){
			case 'd':
				flag = 1;
				argv_num1 = argv_num1 + 2;
				argv_num2 = argv_num2 + 2;
				break;
		}
	}


	if((rfp = fopen(argv[argv_num1],"r")) == NULL){
		perror("fopen: unix.txt");
		exit(1);
	}

	if((wfp = fopen(argv[argv_num2],"w")) == NULL){
		perror("fopen:unix.out");
		exit(1);
	}
	
	if(flag == 1){
		printf("암호화");
		while((c = fgetc(rfp)) != EOF){
			c = c - atoi(argv[2]);
			fputc(c,wfp);
		}
	}
	else{
		while((c = fgetc(rfp)) != EOF){
			fputc(c,wfp);
		}
	}

	fclose(rfp);
	fclose(wfp);

	return 0;

}
