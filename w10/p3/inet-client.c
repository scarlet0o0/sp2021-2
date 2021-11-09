#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PORTNUM 9000
#define TRUE 1
int main(void){
	char buf[256];
	struct sockaddr_in sin;
	int sd;

	if((sd = socket(AF_INET, SOCK_STREAM,0)) == -1) {
		perror("socket");
		exit(1);
	}

	memset((char *)&sin, '\0',sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORTNUM);
	sin.sin_addr.s_addr = inet_addr("172.18.0.1");

	if(connect(sd, (struct sockaddr *)&sin, sizeof(sin))){
		perror("connect");
		exit(1);
	}

	if(recv(sd, buf, sizeof(buf), 0) == -1)
	{
		perror("recv");
		exit(1);
	}

	printf("%s\n",buf);


	memset((char *)&buf,'\0',sizeof(buf));

	printf("문자열을 입력하세요: ");
	scanf("%s",buf);

	if(send(sd,buf,strlen(buf)+1,0) == -1)
	{
		perror("send");
		exit(1);
	}
	
	if(strcmp(buf,"ECHO") == 0)
	{
		while(1)
		{
			memset((char *)&buf,'\0',sizeof(buf));

			printf("문자열을 입력하세요: ");
			scanf("%s",buf);

			if(send(sd,buf,strlen(buf)+1,0) == -1)
			{
				perror("send");
				exit(1);
			}

			memset((char *)&buf,'\0',sizeof(buf));
	
			if(recv(sd, buf, sizeof(buf), 0) == -1)
			{
				perror("recv");
				exit(1);
			}
			printf("[echo]: %s\n",buf);
			if(strcmp(buf,"quit") == 0) break;
		}

	}
	else{
		memset((char *)&buf,'\0',sizeof(buf));
	
		if(recv(sd, buf, sizeof(buf), 0) == -1)
		{
			perror("recv");
			exit(1);
		}	

		printf("From Server : %s\n",buf);
	}

	close(sd);
	return 0;
}
