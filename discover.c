#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int sum = 0;

void    *runner(void *param)
{
    int i;
    int upper = atoi(param);

    i = 1;
    while (i <= upper)
    {
        sum += i;
        usleep(100);
        i++;
    }
    printf("the sum is: %d\n", sum);
    pthread_exit(0);
}

int main(int argc, char **argv)
{
    pthread_t tid1;
    pthread_t tid2;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_create(&tid1, &attr, runner, argv[1]);
    pthread_create(&tid2, &attr, runner, argv[1]);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("sum = %d\n", sum);
}