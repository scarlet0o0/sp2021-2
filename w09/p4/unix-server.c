#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <fcntl.h>
#define SOCKET_NAME "qsocket"

int main(void){
	int sd, len,nsd,clen;
	char buf[256];
	struct sockaddr_un ser, cli;
	
	int fd, n;
	char rbuf[20];
	
	clen = sizeof(cli);
	if((sd = socket(AF_UNIX,SOCK_STREAM,0)) ==-1)
	{
		perror("socket");
		exit(1);
	}

	memset((char *)&ser, '0', sizeof(struct sockaddr_un));
	ser.sun_family = AF_UNIX;
	strcpy(ser.sun_path,SOCKET_NAME);
	len = sizeof(ser.sun_family) + strlen(ser.sun_path);
	
	unlink(SOCKET_NAME);
	if(bind(sd,(struct sockaddr *)&ser,len))
	{
		perror("bind");
		exit(1);
	}

	if(listen(sd, 5) <0)
	{
		perror("listen");
		exit(1);
	}

	printf("Waiting...\n");

	if((nsd = accept(sd, (struct sockaddr *)&cli, &clen)) == -1)
	{
		perror("accept");
		exit(1);
	}

	if(recv(nsd,buf,sizeof(buf),0) == -1)
	{
		perror("recv");
		exit(1);
	}

	printf("Received Mesage : %s\n",buf);
	
	fd = open(buf,O_RDONLY);
	if(fd == -1)
	{
		memset((char*)&buf,'\0',sizeof(buf));
		strcpy(buf,"File not exist!!");

		if(send(nsd,buf,strlen(buf),0) == -1)
		{
			perror("send");
			exit(1);
		}

		exit(1);
	}

	lseek(fd,0,SEEK_SET);

	n = read(fd, rbuf, 16);
	printf("읽은 글자 -> %d\n",n);

	printf("파일의 내용:%s\n",rbuf);

	if(send(nsd,rbuf,strlen(rbuf),0) == -1)
	{
		perror("send");
		exit(1);
	}
	
	close(fd);
	close(nsd);
	close(sd);
	return 0;
}

