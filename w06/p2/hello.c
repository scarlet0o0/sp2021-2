#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(void){
	int random_sleep_num;
	srand(time(NULL));	
	random_sleep_num = (rand() %(30-10+1)+10);
	printf("Hello word begins\n");
	//printf("랜덤숫자 :  %d\n",random_sleep_num);
	sleep(random_sleep_num);
	printf("HEllo word ends\n");

	return 0;
}
