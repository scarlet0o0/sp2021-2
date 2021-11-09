#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PORTNUM 9002
#define BUFLEN 256

int main(void) {
	int sock;
	char buf[BUFLEN];
    	struct sockaddr_in server;


    	memset((char *)&server, '\0', sizeof(server));
    	server.sin_family = AF_INET; 
    	server.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    	server.sin_port = htons(PORTNUM); 

    	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
    	{
        	perror("socket"); 
		exit(1);
    	}

    	if (connect(sock, (struct sockaddr *)&server, sizeof(server))) 
    	{
        	perror("connect"); exit(1);
    	}
	printf("[Info] Connected to the server!\n");


	while(1){
		printf("[ME]: ");
		fgets(buf, BUFLEN, stdin); 
		if (send(sock, buf, strlen(buf)+1, 0) == -1)
		{
			perror("send"); 
			break;
		}

		memset(buf, '\0', BUFLEN); 

		if (recv(sock, buf, BUFLEN, 0) == -1) 
		{ 
	        	perror("recv"); 
			break;
		}

		printf("[server]: %s\n", buf);

		memset(buf, '\0', BUFLEN);


	}

    	close(sock); 
    	return 0;
}

