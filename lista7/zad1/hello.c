#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define THREAD_NO 14

typedef struct
{
    int thread_id;
} hello_scr_arg;

void* hello_scr(void* void_arg)
{
    hello_scr_arg* arg = void_arg;

    //sleep(1);
    printf("Hello SCR. Written by thread %i\n", arg->thread_id);

    pthread_exit(NULL);
}

int main()
{
    pthread_t threads_id[THREAD_NO];
    hello_scr_arg threads_args[THREAD_NO];

    for (int i = 0; i < THREAD_NO; ++i)
    {
        threads_args[i].thread_id = i;
        pthread_create(threads_id + i, NULL, hello_scr, threads_args + i);
    }

    for (int i = 0; i < THREAD_NO; ++i)
    {
        pthread_join(threads_id[i], NULL);
    }

    pthread_exit(NULL);
}
