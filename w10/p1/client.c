#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "info.h"

int main(void) {
	int sock;
	char buf[BUFLEN];
    	struct sockaddr_in server;

    	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
    	{
        	perror("socket"); exit(1);
    	}

	
    	memset((char *)&server, '\0', sizeof(server));
    	server.sin_family = AF_INET; 
    	server.sin_addr.s_addr = inet_addr(SERVERIPADDR); 
    	server.sin_port = htons(PORTNUM); 

	
    	if (connect(sock, (struct sockaddr *)&server, sizeof(server))) 
    	{
        	perror("connect"); exit(1);
    	}
	printf("[Info] Connected to the server!\n");

    	while(TRUE)
	{
		//printf("[Info] waiting for a message from server...\n");
		memset(buf, '\0', BUFLEN); 
	    	if (recv(sock, buf, BUFLEN, 0) == -1) 
		{ 
	        	perror("recv"); break;
	    	}
		if(strncmp(buf,QUITMSG, strlen(QUITMSG)) == 0) 
		{
			printf("[Info] [YOU] quit!\n");
			break;
		}
	    	printf("[YOU]: %s\n", buf); 
	
		memset(buf, '\0', BUFLEN); 
		printf("[ME]: ");
		fgets(buf, BUFLEN, stdin); 
	    	if (send(sock, buf, strlen(buf)+1, 0) == -1)
	    	{	 
			perror("send"); break;
		}
		if(strncmp(buf,QUITMSG, strlen(QUITMSG)) == 0) 
		{
			printf("[Info] [ME] quit!\n");
			break;
		}
	}
    	close(sock); 
    	return 0;
}

