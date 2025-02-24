#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *routine(void *val)
{
	int index = *(int *)val;
	int sum = 0;
	for (int i = 0;i < 5; i++)
	{
		sum += primes[index + i];
	}
	printf("local sum is: %d\n", sum);
	*(int *)val = sum;
	return (val);
}

int main(void)
{
	pthread_t th[2];
	int h[] = {0, 5}; 
	
	int sum = 0;

	for(int i = 0; i < 2; i++)
		pthread_create(&th[i], NULL, &routine, &h[i]);
	for (int  i = 0; i < 2; i++)
	{
		int *r;
		pthread_join(th[i], (void**) &r);
		sum += *r;
	}
	printf("sum is: %d\n", sum);
}