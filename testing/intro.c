#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void	*routine()
{
	printf("called from a thread\n");
	sleep(3);
	printf("hi!!!!!!\n");
}

int main(void)
{
	pthread_t	t1;
	pthread_t	t2;
	pthread_create(&t1, NULL, &routine, NULL);
	pthread_create(&t2, NULL, &routine, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

}