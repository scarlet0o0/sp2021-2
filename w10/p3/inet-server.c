#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define PORTNUM 9000
#define TRUE 1
int main(void){
	char buf[256];
	struct sockaddr_in sin, cli;
	int sd, ns, clientlen = sizeof(cli);
	int mode = 0;

	char hostname[20];
	char ipbuf[20];
	char portbuf[20];

	time_t seconds = time(NULL);
	struct tm *now = localtime(&seconds);

	if((sd = socket(AF_INET, SOCK_STREAM,0)) == -1) {
		perror("socket");
		exit(1);
	}

	memset((char *)&sin, '\0',sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORTNUM);
	sin.sin_addr.s_addr = inet_addr("172.18.0.1");

	if(bind(sd, (struct sockaddr *)&sin, sizeof(sin))) {
		perror("bind");
		exit(1);
	}

	if(listen(sd, 5)){
		perror("listen");
		exit(1);
	}

	if((ns = accept(sd, (struct sockaddr *)&cli, &clientlen)) == -1){
		perror("accept");
		exit(1);
	}

	sprintf(buf,"<Available Services>\n1.ECHO server <ECHO>\n2.Get server info <SINFO>\n 3.Get server time <STIME>");
	if((send(ns, buf, strlen(buf)+1, 0)) == -1)
	{
		perror("send");
		exit(1);
	}

	memset((char *)&buf,'\0',sizeof(buf));

	if(recv(ns,buf,sizeof(buf),0) == -1)
	{
		perror("recv");
		exit(1);
	}

	if(strcmp(buf,"ECHO") == 0) 
	{
		mode = 1;
	}
	else if(strcmp(buf,"SINFO") == 0)
	{
		mode = 2;
	}
	else if(strcmp(buf,"STIME") == 0) 
	{
		mode = 3;
	}

	switch(mode){
		case 1:
			while(1)
			{
				memset((char *)&buf,'\0',sizeof(buf));

				if(recv(ns,buf,sizeof(buf),0) == -1)
				{
					perror("recv");
					exit(1);
				}

				if(strcmp(buf,"QUIT") == 0) break;

				if((send(ns, buf, strlen(buf)+1, 0)) == -1)
				{
					perror("send");
					exit(1);
				}	

			}
			break;
		case 2:
			memset((char *)&buf,'\0',sizeof(buf));

			strcat(buf,"호스트명: ");
			gethostname(hostname,20);
			strcat(buf,hostname);
			
			strcat(buf,"\n ip번호: ");
			strcpy(ipbuf,inet_ntoa(sin.sin_addr));
			strcat(buf,ipbuf);

			sprintf(portbuf,"\n 포트번호: %d",ntohs(sin.sin_port));
			strcat(buf,portbuf);
			
			if((send(ns, buf, strlen(buf)+1, 0)) == -1)
			{
				perror("send");
				exit(1);
			}
			break;
		case 3:
			memset((char *)&buf,'\0',sizeof(buf));
			sprintf(buf,"[%04d/%02d/%02d] %02d:%02d:%02d\n", 1900 + now->tm_year,now->tm_mon + 1, now->tm_mday, now->tm_hour,now->tm_min, now->tm_sec);
			if((send(ns, buf, strlen(buf)+1, 0)) == -1)
			{
				perror("send");
				exit(1);
			}
			break;
		default:
			sprintf(buf,"오류");
			if((send(ns, buf, strlen(buf)+1, 0)) == -1)
			{
				perror("send");
				exit(1);
			}
	}
			

	close(ns);
	close(sd);

	return 0;
}
