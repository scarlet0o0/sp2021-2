#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void){
	int pd1,pd2, n,f;
	char buf[256];

	//============================================
	
	printf("client ====\n");

	if(mkfifo("./c_FIFO_s",0666) == -1)
	{
	//	perror("open");
	//	exit(1);
	}

	if((pd1 = open("./c_FIFO_s",O_WRONLY)) == -1)
	{
		perror("open");
		exit(1);
	}
	if((pd2 = open("./s_FIFO_c",O_RDONLY)) == -1)
	{
		perror("open < ./s_fifo_c > ");
		exit(1);
	}



	while(1)
	{
		printf("<GET> ");
		scanf("%s",buf);

		n = write(pd1,buf,strlen(buf)+1);
		if(n == -1)
		{
			perror("write");
			exit(1);
		}

		if(strcmp(buf,"exit") == 0)
			break;
		
		memset(buf,0,256);

		n = read(pd2,buf,256);
		//`write(1,buf,n);
		if( n == -1)
		{
			perror("read");
			exit(1);
		}
	
		if (strcmp(buf,"error") == 0)
		{	
			printf("File does not exist\n");
		}
		else
		{
			printf("내용:%s",buf);
			f = open("download_hello.txt",O_WRONLY|O_CREAT|O_TRUNC,0666);
			write(f,buf,strlen(buf));
			close(f);
		}
	}
	close(pd1);
	close(pd2);

	return 0;
}

