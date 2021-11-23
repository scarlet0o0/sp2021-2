#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct StudentInfo {
	char name[20];
	char major[20];
	char univ[20];
}StudentInfo;

void *start_thread(void *stu)
{
	int i;
	StudentInfo *s = (StudentInfo *)stu;
	for(int i = 0; i < 10 ; i++){
		sleep(1);
		printf("%s\n",s -> name);
		sleep(1);
	}
	return stu;
}

int main(){

	pthread_t thing1, thing2;

	struct StudentInfo stu1 = {.name="Brad Pitt",.major="Computer Engineering",.univ="Holly University"};
	struct StudentInfo stu2 = {.name="Angelina Jollie",.major="Computer Science",.univ="Wood University"};

	pthread_create(&thing1, NULL, start_thread, (void *) &stu1);
	pthread_create(&thing2, NULL, start_thread, (void *) &stu2);

	pthread_join(thing1, NULL);
	pthread_join(thing2, NULL);

	return 0;
}
