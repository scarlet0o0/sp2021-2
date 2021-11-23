#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct Account{
	int saving;
	int balance;
	pthread_mutex_t mutex;
	//int amount;
}Account;

int disburse_maney(struct Account *account, int amount){
	account -> saving = account -> saving - amount;
	if(account -> saving != account -> balance)
	{
		printf("[d]실제 계좌잔액: %d, 통잔잔액: %d\n", account->saving, account->balance);
		printf("실제 계좌잔액과 통장잔액이 같지 않다\n");
		exit(1);	
	}
	

	return 0;
}
void *start_thread1(void *a)
{
	Account *account = (Account *)a;
	pthread_mutex_lock(& account -> mutex);
	const int balance = account -> balance;
	sleep(1);
	int amount = 300;

	if(balance < amount)
	{
		printf("잔액부족");
		exit(1);
	}

	account -> balance = balance - amount;
	disburse_maney(account,amount);
	printf("[t1]실제 계좌잔액: %d, 통잔잔액: %d, 인출금액:%d\n", account->saving, account->balance,amount);
	pthread_mutex_unlock(& account -> mutex);
	return 0;
}

void *start_thread2(void *a)
{
	Account *account = (Account *)a;
	pthread_mutex_lock(& account -> mutex);

	const int balance = account -> balance;

	sleep(1);
	int amount = 400;

	if(balance < amount)
	{
		printf("잔액부족");
		exit(1);
	}

	account -> balance = balance - amount;
	disburse_maney(account,amount);
	printf("[t2]실제 계좌잔액: %d, 통잔잔액: %d, 인출금액:%d\n", account->saving, account->balance,amount);

	pthread_mutex_unlock(& account -> mutex);

	return 0;
}




int main(){

	pthread_t thing1, thing2;
	struct Account a = {.saving = 500, .balance = 500, .mutex = PTHREAD_MUTEX_INITIALIZER};

	printf("실제 계좌잔액: %d, 통잔잔액: %d\n", a.saving, a.balance);
	pthread_create(&thing1, NULL, start_thread1, (void *) &a);
	pthread_create(&thing2, NULL, start_thread2, (void *) &a);
	
	pthread_join(thing1, NULL);
	pthread_join(thing2, NULL);
	printf("실제 계좌잔액: %d, 통잔잔액: %d\n", a.saving, a.balance);
	return 0;
}
