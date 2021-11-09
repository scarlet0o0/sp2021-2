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
	char buf[BUFLEN];
    	struct sockaddr_in server, client;
    	int access_sock, comm_sock, len;
	
    	if ((access_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
    	{
        	perror("socket"); exit(1);
    	}

    	memset((char *)&server, '\0', sizeof(server));
    	server.sin_family = AF_INET;
    	server.sin_addr.s_addr = htonl(INADDR_ANY); 
    	server.sin_port = htons(PORTNUM); 

	
    	if (bind(access_sock, (struct sockaddr *)&server, sizeof(server))) 
    	{
        	perror("bind"); exit(1);
    	}

	
    	if (listen(access_sock, LISTENLEN)) 
    	{
        	perror("listen"); exit(1);
    	}

    
	//printf("[Info] Waiting for client connect request...\n");
        if ((comm_sock = accept(access_sock, (struct sockaddr *)&client, &len)) == -1) 
	{
            	perror("accept"); 
		exit(1);
        } 
        sprintf(buf, "%s", inet_ntoa(client.sin_addr));
	printf("[Info] Client connected! (%s)\n", buf);

	while(TRUE)
	{
		memset(buf,0,BUFLEN);
		printf("[ME]: ");
		fgets(buf, BUFLEN, stdin); 	
		if( send(comm_sock, buf, strlen(buf)+1, 0) == -1 )
		{
			perror("send"); 
			break;
		}
		if( strncmp(buf, QUITMSG, strlen(QUITMSG)) == 0 ) 
		{
			printf("[Info] [ME] quit!\n");
			break;
		}


		//printf("[Info] waiting for a message from client...\n");
	        if (recv(comm_sock, buf, BUFLEN, 0) == -1) 
		{
    	        	perror("recv"); 
			break;
        	}
	        printf("[YOU]: %s\n", buf); 
		if( strncmp(buf, QUITMSG, strlen(QUITMSG)) == 0 ) 
		{
			printf("[Info] [YOU] quit!\n");
			break;
		}
			
	}
        close(comm_sock); 
    	close(access_sock); 

    	return 0;
}

