#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

int main(void)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL) == 0)
    {
        printf("seconds:        %ld\n", tv.tv_sec);
        printf("micro seconds:  %ld\n", tv.tv_usec);
    }
    int i = 0;
    while(i < 10)
    {
        gettimeofday(&tv, NULL);
        int num = (tv.tv_usec * i) % 10 + 1;
        printf("random num: %d\n", num);
        i++;
    }
    
}