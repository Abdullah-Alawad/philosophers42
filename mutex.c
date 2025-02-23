#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_shared_data
{
    pthread_mutex_t lock;
    int data;
} t_shared_data;

void *increment(void *arg)
{
    t_shared_data *data = (t_shared_data *)arg;

    printf("hi\n"); // all threads will run this at the same time
    pthread_mutex_lock(&data->lock);
    (*data).data++; // only one thread at a time will run this
    printf("shared data: %d\n", data->data);
    sleep(1);
    pthread_mutex_unlock(&data->lock);
}


int main(void)
{
    pthread_t thread[10];
    t_shared_data data;

    data.data = 0;
    pthread_mutex_init(&data.lock, NULL);

    int i = 0;
    while (i < 10)
    {
        pthread_create(&thread[i], NULL, increment, &data);
        i++;
    }
    i = 0;
    while (i < 10)
    {
        pthread_join(thread[i], NULL);
        i++;
    }
    pthread_mutex_destroy(&data.lock);
}