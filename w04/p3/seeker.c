#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>


int main(int argc, char *argv[]){
	
	int fd,n;
	char *buf[2];
	fd = open(argv[1],O_RDONLY,0644);
	if(fd == -1){
		perror("Creat");
		exit(1);
	}
	

	
	if(strcmp(argv[2],"begin") == 0 ){
		printf("argv[2] = begin\n");
		lseek(fd,0,SEEK_SET);
		for(int i = 0; i< atoi(argv[3]);i++){
			n=read(fd,buf,1);
			if(n == 0){
				lseek(fd,0,SEEK_SET);
				i--;
				continue;

			}
			buf[n] = '\0';
			printf("[%d] 유니코드:%d  vuf : %c\n",i+1,buf[0],buf[0]);

		}


	}
	else if(strcmp(argv[2],"end") == 0){
		printf("argv[2] = end\n");
		lseek(fd,0,SEEK_END);
		for(int i = 0; i< atoi(argv[3]);i++){
			n=read(fd,buf,1);
			if(n == 0){
				lseek(fd,0,SEEK_SET);
				i--;
				continue;

			}
			buf[n] = '\0';
			printf("[%d] 유니코드:%d  vuf : %c\n",i+1,buf[0],buf[0]);

		}
	}
	else if(strcmp(argv[2],"mid") == 0){
		printf("argv[2] = mid\n");
		n=lseek(fd,0,SEEK_END)/2;
		lseek(fd,n,SEEK_SET);
		for(int i = 0; i< atoi(argv[3]);i++){
			n=read(fd,buf,1);
			if(n == 0){
				lseek(fd,0,SEEK_SET);
				i--;
				continue;
			}
			buf[n] = '\0';
			printf("[%d] 유니코드:%d  vuf : %c\n",i+1,buf[0],buf[0]);

		}


	}
	else{
		int number = atoi(argv[2]);	
		printf("argv[2] = 숫자\n");
		if(number > -1){
			n=lseek(fd,atoi(argv[2]),SEEK_SET);
			for(int i = 0; i< atoi(argv[3]);i++){
				n=read(fd,buf,1);
				if(n == 0){
					printf("줄바꿈\n");
				       	lseek(fd,0,SEEK_SET);
					i--;
					continue;
				}
				buf[n] = '\0';
				printf("[%d] 유니코드:%d  vuf : %c\n",i+1,buf[0],buf[0]);
			}
		}
		else{
			lseek(fd,atoi(argv[2]),SEEK_END);
			for(int i = 0; i< atoi(argv[3]);i++){
				n=read(fd,buf,1);
				if(n == 0) {
					lseek(fd,0,SEEK_SET);
					continue;
				}
				buf[n] = '\0';
				printf("[%d] 유니코드:%d  vuf : %c\n",i+1,buf[0],buf[0]);

			}


		}
	}

	close(fd);



	return 0;
}
