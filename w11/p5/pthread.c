#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t lock3 = PTHREAD_MUTEX_INITIALIZER;

void *function1(void* arg){
	pthread_mutex_lock(&lock3);

        sleep(1);       //main thread가 먼저 실행할 여지를 줌
        printf("[tid1] thread start\n");

        pthread_mutex_lock(&lock2);
        pthread_mutex_lock(&lock1);

        printf("[tid1] critical section \n");

        pthread_mutex_unlock(&lock1);
        pthread_mutex_unlock(&lock2);

        printf("[tid1]thread end\n");

        pthread_mutex_unlock(&lock3);
}
void *function2(void* arg)
{
	pthread_mutex_lock(&lock3);

        printf("[tid2] thread start\n");

        pthread_mutex_lock(&lock1);
        sleep(5);               //thread가 lock2를 먼저 실행할 여유를 줌
        pthread_mutex_lock(&lock2);
        printf("[tid2] critical section \n");

        pthread_mutex_unlock(&lock2);
        pthread_mutex_unlock(&lock1);

        printf("[tid2] main thread end\n");

        pthread_mutex_unlock(&lock3);
}

int main(){
        pthread_t tid1,tid2;

	pthread_create(&tid1,NULL,function1,NULL);
        pthread_create(&tid2,NULL,function2,NULL);

    
        pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

}
