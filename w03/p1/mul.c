#include<stdio.h>

int mul(){
	int num1,num2,hap = 0;
	printf("Enter two number :");
	scanf("%d %d",&num1,&num2);

	hap = num1 * num2;

	printf("Result : %d + %d = %d",num1,num2,hap);

	return hap;
}
