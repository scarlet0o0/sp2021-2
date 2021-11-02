#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/un.h>

#define SOCKET_NAME "qsocket"

int main(void){
	int sd, len;
	char buf[256];
	struct sockaddr_un ser;

	if((sd = socket(AF_UNIX,SOCK_STREAM,0)) ==-1)
	{
		perror("socket");
		exit(1);
	}

	memset((char *)&ser, '0', sizeof(ser));
	ser.sun_family = AF_UNIX;
	strcpy(ser.sun_path,SOCKET_NAME);
	len = sizeof(ser.sun_family) + strlen(ser.sun_path);

	

	if(connect(sd, (struct sockaddr *)&ser, len) < 0) 
	{
		perror("bind");
		exit(1);
	}
	
	printf("파일위치 : ");
	scanf("%s",buf);
	if(send(sd,buf,strlen(buf),0) == -1)
	{
		perror("send");
		exit(1);
	}
	
	memset((char *)&buf, '\0', sizeof(buf));

	if(recv(sd,buf,sizeof(buf),0) == -1)
	{
		perror("recv");
		exit(1);
	}

	printf("%s",buf);

	close(sd);
	return 0;
}

