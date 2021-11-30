#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{
	int fd;
	pid_t pid;
	caddr_t addr;
	struct stat statbuf;


	if (argc != 2)
	{
		fprintf(stderr, "Usage : %s filename\n",argv[0]);
		exit(1);
	}

	if(stat(argv[1], &statbuf) == -1) 
	{
		perror("stat");
		exit(1);
	}

	if((fd = open(argv[1], O_RDWR)) == -1)
	{
		perror("open");
		exit(1);
	}

	addr = mmap(NULL, statbuf.st_size, PROT_READ|PROT_WRITE, \
			MAP_SHARED, fd, (off_t)0);
	if(addr == MAP_FAILED)
	{
		perror("mmap");
		exit(1);
	}
	close(fd);
	
	switch (pid = fork()) {
		case -1:
			perror("fork");
			exit(1);
			break;
		case 0:

			srand(time(0));
			sleep(1);
			for(int i = 0; i<100;i++){
				int num;
				num = rand() %100;
				//printf("num : %d\n",num);
				addr[num] = 'p';
				sleep(1);
				//printf("3. Child Process : addr=%s",addr);
			}
			break;

		default :

			sleep(1);
			srand(time(0));
			for(int i = 0; i < 100 ;i++){
				int num;
				num = rand() % 100;
				//printf("num : %d\n",num);
				addr[num] = 'c';
				sleep(1);
				//printf("Parent process : addr=%s",addr);
			}
			break;
	}

	return 0;

}
