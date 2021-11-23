#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(void) {
	FILE *fp;
	char buf[999];
	int len;
	fp = popen("ls /", "r");
	if (fp == NULL)
	{
		fprintf(stderr, "popen failed\n");
		exit(1);
	}

	while(fgets(buf, sizeof(buf), fp))
	{
		if(strstr(buf,"s")!=NULL)
		{
			printf("%s", buf);
		}
	}

	

	pclose(fp);

	return 0;
}
