#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	*roll()
{
	int res = (rand() % 6) + 1;
	int *result = malloc(sizeof(int));
	*result = res;
	//printf("dice res: %d\n", res);
	printf("add res: %p\n", result);
	return ((void *)result);
}

int main(void)
{
	pthread_t th;
	int *res;
	srand(time(NULL));

	pthread_create(&th, NULL, &roll, NULL);

	pthread_join(th, (void **) &res);
	printf("result in main: %d\n", *res);
	printf("add in main: %p\n", res);
	free(res);
}