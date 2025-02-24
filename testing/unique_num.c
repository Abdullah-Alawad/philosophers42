#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *print_prime(void *val)
{
	int index = *(int *)val;
	printf("%d ", index);
}

int main(void)
{
	pthread_t th[10];
	int i;
	for (i = 0; i < 10; i++)
		pthread_create(&th[i], NULL, &print_prime, primes + i);
	for (i = 0; i < 10; i++)
		pthread_join(th[i], NULL);
}