#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(int argc,char *argv[]){
	struct stat buf;
	int kind;
	char *type_f;	
	stat(argv[1],&buf);

	kind = buf.st_mode & S_IFMT;

	switch(kind){
		case S_IFIFO:
			type_f = "FIFO";
			break;
		case S_IFDIR:
			type_f = "Directory";
			break;
		case S_IFREG:
			type_f = "Regular File";
			break;
	}

	printf("Filename: %s\n",argv[1]);
	printf("-inode numer:%d\n",(int)buf.st_ino);
	printf("-File type:%s\n",type_f);
	printf("-Permission:%o\n",(unsigned int)(buf.st_mode & (S_IRWXU + S_IRWXG + S_IRWXO)));
	printf("-Numer of links:%o\n",(unsigned int)buf.st_nlink);
	printf("-Size:%d\n",(int)buf.st_size);

	return 0;

}
