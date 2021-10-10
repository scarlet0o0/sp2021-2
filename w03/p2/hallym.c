#include<stdio.h>
#include<getopt.h>

int main(int argc, char*const*argv){
	int n;
	extern char *optarg;
	extern int optind;

	n = getopt(argc, argv,"au:h");
	switch(n){
		case 'a':
			printf("Welcome to System Programming (2019-2)\n");
			break;
		case 'u':
			printf("Nice to meet you, %s\n",optarg);
			break;
		case 'h':
			printf("Option : -a =>printf(Welcome to System Programming (2019-2)\n");
			printf("Option : -u => printf(Nice to meet you)\n");
			printf("Option : -h => hellp  \n");
			break;
		default:
			printf("ERROR: please provide at least one\n");
			break;
	}
		
	return 0;
}	
