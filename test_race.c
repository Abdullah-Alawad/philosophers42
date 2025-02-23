#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int mails = 0;
pthread_mutex_t mutex;

void	*routine()
{
	int	i = 0;
	
	while (i < 10000000)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
		i++;
	}
}

int	main(void)
{
	int	i = 0;
	pthread_t t[8];

	pthread_mutex_init(&mutex, NULL);
	while (i < 8)
	{
		if (pthread_create(&t[i], NULL, &routine, NULL) != 0)
			return (1);
		printf("thread num %d has started\n", i);
		i++;
	}
	i = 0;
	while (i < 8)
	{
		pthread_join(t[i], NULL);
		printf("thread num %d has finished\n", i);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	printf("number of mails: %d\n", mails);
}