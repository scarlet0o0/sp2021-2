#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void){
	int pd1,pd2,n,f;
	char buf[256],inmsg[80];

	// ==============================================
	
	printf("server ====\n");

	if(mkfifo("./s_FIFO_c",0666) == -1)
	{
		//perror("open");
		//exit(1);
	}

	if((pd1= open("./c_FIFO_s",O_RDONLY)) == -1)
	{
		perror("open3");
		exit(1);
	}
	if((pd2 = open("./s_FIFO_c",O_WRONLY)) == -1)
	{
		perror("open <./c_fifo_s>");
		exit(1);
	}

	while(1){	
		write(1,"From client : ",14);

		n = read(pd1,inmsg,80);
		write(1,inmsg,n);
		if(n == -1)
		{
			perror("read");
			exit(1);
		}

		if(strcmp(buf,"exit") == 0)
			break;
		
		if((f = open(inmsg,O_RDONLY)) == -1)
		{
			//파일이 존재하지않을 경우 파이프를 통해 
			//오류메시지 전송
			sprintf(buf,"error");
			write(pd2,buf,strlen(buf)+1);
		}
		else
		{
			read(f,buf,sizeof(buf));
			write(pd2,buf,strlen(buf)+1);
		}
		printf("\n");
	}

	close(pd1);
	close(pd2);

	return 0;
}

