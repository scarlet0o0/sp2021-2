#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
void a(struct stat *buf,char *s);
int main(int argc,char *argv[]){
	
	struct stat buf;
	char sr[10];
	stat(argv[1],&buf);
	printf("%s\n",sr);	
	if(argc == 2){
		a(&buf,sr);
		printf("%s\n",sr);
		
	
	}
	else if(argc ==3 ){
		if(atoi(argv[1]) & S_IRWXU){
			printf("---\n");
		}
		printf("n %o\n",100000+atoi(argv[1]));
	}


	return 0;
}

void a(struct stat *buf, char *s){
	if(buf->st_mode & S_IRWXU )s[0]= 'r';
	else s[0] = '-';
	if(buf->st_mode & S_IRUSR)s[1]= 'w';
	else s[1] = '-';
	if(buf->st_mode & S_IWUSR )s[2]= 'x';
	else s[2] = '-';
	if(buf->st_mode & S_IXUSR)s[3]= 'r';
	else s[3] = '-';
	if(buf->st_mode & S_IRWXG)s[4]= 'w';
	else s[4] = '-';
	if(buf->st_mode & S_IWGRP)s[5]= 'x';
	else s[5] = '-';
	if(buf->st_mode & S_IRWXO)s[6]= 'r';
	else s[6] = '-';
	if(buf->st_mode & S_IROTH)s[7]= 'w';
	else s[7] = '-';
	if(buf->st_mode & S_IXOTH)s[8]= 'x';
	else s[8] = '-';

}
