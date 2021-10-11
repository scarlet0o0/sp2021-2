#include <stdio.h>
#include <sys/times.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

//#define CLK_TCK ((clock_t)_SC_CLK_TCK)

void func_01(int *arr,int s);
void func_ON(int *arr,int s);
void func_ON2(int *arr,int s);
int main(int argc,char* argv[]){
	//double CLK_TCK = ((clock_t)_SC_CLK_TCK);
	int size = 59999;
	int arr[size];
	for (int i = 0 ; i<size ; i++){
		arr[i] = i;
	}

	time_t t;
	struct tms mytms;
	clock_t t1_1,t1_2,t2_1,t2_2,t3_1,t3_2;
	
	if ((t1_1 = times(&mytms)) == -1){ 
		perror("times1_1"); 
		exit(1);
	}
	func_01(arr,size);
	if ((t1_2= times(&mytms)) == -1){ 
		perror("times1_1"); 
		exit(1);
	}
	if ((t2_1 = times(&mytms)) == -1){ 
		perror("times1_1"); 
		exit(1);
	}
	func_ON(arr,size);
	if ((t2_2= times(&mytms)) == -1){ 
		perror("times1_1"); 
		exit(1);
	}
	//printf("2\n");
	if ((t3_1 = times(&mytms)) == -1){ 
		perror("times1_1"); 
		exit(1);
	}
	func_ON2(arr,size);
	if ((t3_2= times(&mytms)) == -1) {
		perror("times1_1"); 
		exit(1);
	}
	//printf("3\n");
	printf("func_01 takes %.1f seconds.\n",((double)(t1_2-t1_1)/CLOCKS_PER_SEC)*10000);
	printf("func_ON takes %.1f seconds.\n",((double)(t2_2-t2_1)/CLOCKS_PER_SEC)*10000);
	printf("func_ON2 takes %.1f seconds.\n",((double)(t3_2-t3_1)/CLOCKS_PER_SEC)*10000);
	return 0;
}

void func_01(int *arr,int s){
	int num; 
	num = arr[0];
}
void func_ON(int *arr,int s){
	int num;
	num = 0;
	for (int i = 0; i <s ; i++){
		num += arr[i];
	}

}
void func_ON2(int *arr,int s){
	int num;
	num = 0;
	for (int i = 0; i <s ;i++){
		for(int j = 0; j < s ;j++){
			num +=arr[i];
		}
	}
}
