#include<stdio.h>
#include<stdlib.h>

void add(int**arr,int num,int i,int*n,int*sum,int*size);
void sizeup(int**arr, int*size);
void print_arr(int* arr,int n);
void sub(int**arr,int i,int*n,int*sum,int*size);
void sizedown(int**arr, int*size);

int main(){
	int size = 10;
	int n = 0;
	int* arr;
	int sum = 0;
	
	arr = (int*)malloc(sizeof(int)*size);

	for(int j= 1;j<=100;j++){
		int j1 = j-1;
		add(&arr,j,j1,&n,&sum,&size);
	}

	//print_arr(arr,n);
	printf("size: %d, n: %d,sum: %d\n",size,n,sum);

	for(int j= 99;j>=10;j--){
		sub(&arr,j,&n,&sum,&size);
	}

	//print_arr(arr,n);
	printf("size: %d, n: %d,sum: %d\n",size,n,sum);

	free(arr);
	return 0;
}

void add(int**arr,int num,int i,int*n,int*sum,int*size){
	if(*n >= *size){
		sizeup(arr,size);
	}
	(*arr)[i] = num;
	*sum+=num;
	*n+=1;

}
void sub(int**arr,int i,int*n,int*sum,int*size){
	int num = (*arr)[i];
	(*arr)[i] = 0;
	*sum-=num;
	*n-=1;
	if(*n <= *size/4 && *size >=10){
		sizedown(arr,size);
	}

}

void sizeup(int**arr, int*size){
	int s = *size*2;
#ifdef DEBUG
	printf("Size up: %d => %d\n",*size,s);
#endif
	int*temp = (int*)malloc(sizeof(int)*s);
	for(int i= 0; i<*size;i++){
		temp[i] = (*arr)[i];
	}
	free(*arr);
	*arr = temp;
	*size = s;
	
}
void sizedown(int**arr, int*size){
	int s = *size/2;
#ifdef DEBUG
	printf("Size down: %d => %d\n",*size,s);
#endif
	int*temp = (int*)malloc(sizeof(int)*s);
	for(int i= 0; i<s;i++){
		temp[i] = (*arr)[i];
	}
	free(*arr);
	*arr = temp;
	*size = s;
	
}

void print_arr(int* arr,int n){
	for(int i = 0; i<n;i++){
		printf("arr[%d] : %d\n",i,arr[i]);
	}
}
