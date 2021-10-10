#include <stdio.h>
#include "head.h"

int main(){
	int n;
	printf("<Calculator Menu>\n");
	printf("1. Add\n");
	printf("2. Sub\n");
	printf("3. Mul\n");
	printf("Enter : \n");
	scanf("%d",&n);
	

	if(n == 1){
		add();
	}
	else if(n == 2){
		sub();
	}
	else if(n == 3){
		mul();
	}



	return 0;
}
