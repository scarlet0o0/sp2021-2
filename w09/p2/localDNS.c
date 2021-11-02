#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argv, char *argc[]){
	struct hostent *hent;
	int ndx;
	sethostent(0);

	hent = gethostbyname(argc[1]);
	//hent = 
	if(hent !=NULL){
		for ( ndx = 0; NULL != hent -> h_addr_list[ndx];ndx++)
			printf("%s\n",inet_ntoa(*(struct in_addr*)hent->h_addr_list[ndx]));
	}
	else{
		printf("Not Found");
	}

	return 0;
}

