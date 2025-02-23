#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>




/*
int	main(void)
{
	int id1 = fork();
	int id2 = fork();
	if (id1 == 0)
	{
		if (id2 == 0)
			printf("(y)id1: %d, id2: %d\n", id1, id2);
		else
			printf("(x)id1: %d, id2: %d\n", id1, id2);
	}
	else
	{
		if (id2 == 0)
			printf("(z)id1: %d, id2: %d\n", id1, id2);
		else
			printf("(m)id1: %d, id2: %d\n", id1, id2);
	}
	while (wait(NULL) != -1 || errno != ECHILD)
	{
		printf("waitin for a child\n");
	}
}
*/