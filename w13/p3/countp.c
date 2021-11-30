#include<stdio.h>


int main(int argc, char *argv[]){
	FILE *fp;
	char ch;
	int num = 0;
	fp = fopen(argv[1],"r");

	while((ch = fgetc(fp)) !=EOF)
	{
		//printf(" ch : %c\n",ch);
		//num++;
		if(ch == 'p'){
			num++;
		}
	}
	//printf("p의 글자수: %d\n",num);
	if(num > 50)
		printf("Parent won\n");
	else if(num < 50)
		printf("CHuild won\n");
	else
		printf("Even");
	
	fclose(fp);

	return 0;

}
