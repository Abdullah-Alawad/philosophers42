#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	*roll(void *result)
{
	int res = (rand() % 6) + 1;
	//int *result = malloc(sizeof(int));
	*result = res;
	printf("dice res: %d\n", res);
	//printf("add res: %p\n", result);
	return ((void *)result);
}

int main(void)
{
	pthread_t th[5];
	int *res = malloc(sizeof(int) * 5);
	int i;
	srand(time(NULL));
	for (i = 0; i < 5; i++)
		pthread_create(&th[i], NULL, &roll, NULL);

	for (i = 0; i < 5; i++)
		pthread_join(th[i], (void**) &res[i]);
	for(i = 0; i < 5; i++)
		printf("in main dice: %d\n", res[i]);

}