#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
	struct servent *port;
	int n;
	int port_num;
	setservent(0);

	for(n = 1; n < 2; n++){
		port_num = atoi(argv[1]);
		printf("port: %d\n",port_num);
		port = getservbyport(ntohs(port_num),"tcp");
		printf("Name=%s\n", port->s_name);
	}

	endservent();

	return 0;
}
