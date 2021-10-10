#include<stdio.h>
#include<getopt.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char *argv[]){
	int rfd,wfd,n;
	char buf[10];	
	
	int option;
	int flag = 0;

	int argv_num1=1,argv_num2=2;
	while(( option = getopt(argc,argv,"c:")) != -1){
		switch(option){
			case 'c':
				flag = 1;
				argv_num1 = argv_num1 +2;
				argv_num2 = argv_num2 +2;
				break;
		}
	}

	rfd = open(argv[argv_num1],O_RDONLY);
	if(rfd == -1){
		perror("error1");
		exit(1);
	}
	wfd = open(argv[argv_num2],O_CREAT|O_WRONLY|O_TRUNC,0644);
	if(wfd == -1){
		perror("error2");
		exit(1);
	}
	
	lseek(rfd, 0,SEEK_SET);
	if(flag == 1){
		printf("암호화");
		while((n = read(rfd,buf,6))>0){
			for(int i = 0 ;i<6;i++){
				//printf("buf[%d] = %d\n",i,buf[i]);
				buf[i] = buf[i]+atoi(argv[2]);
				//printf("buf[%d] = %d\n",i,buf[i]);
			}
			if(write(wfd,buf,n) !=n) perror("Write");}
	}
	else{
		while((n = read(rfd,buf,1))>0)
			if(write(wfd,buf,n) !=n) perror("Write");
	}
	if( n == -1){ perror("Read");}
	
	close(rfd);
	close(wfd);

	
	return 0;
}
