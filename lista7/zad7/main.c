#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <math.h>
#include <stdint.h>

#define THREAD_NO 12
#define ITER_PER_THREAD 10000000ul

typedef struct
{
    uint64_t circle_points;
    uint64_t square_points;
} monte_carlo_data;

void* monte_carlo_thread(void* arg);

int main()
{
    srandom(time(NULL));

    pthread_t threads_id[THREAD_NO];
    monte_carlo_data thread_results[THREAD_NO];

    for (int i = 0; i < THREAD_NO; ++i)
    {
        pthread_create(threads_id + i, NULL, monte_carlo_thread, thread_results + i);
    }

    for (int i = 0; i < THREAD_NO; ++i)
    {
        pthread_join(threads_id[i], NULL);
    }

    monte_carlo_data result_sum = {0u, 0u};
    for (int i = 0; i < THREAD_NO; ++i)
    {
        result_sum.circle_points += thread_results[i].circle_points;
        result_sum.square_points += thread_results[i].square_points;
    }

    double estimated_pi = 4.0 * ( (double) result_sum.circle_points / result_sum.square_points);
    printf("estimated pi: %lf\n", estimated_pi);

    pthread_exit(NULL);
}

void* monte_carlo_thread(void* arg)
{
    uint64_t circle_points = 0u;

    for (uint64_t i = 0; i < ITER_PER_THREAD; ++i)
    {
        double x = random() / (double)(RAND_MAX) - 0.5;
        double y = random() / (double)(RAND_MAX) - 0.5;

        circle_points += (sqrt(x * x + y * y) <= 0.5);
    }

    monte_carlo_data* result = arg;
    result->circle_points = circle_points;
    result->square_points = ITER_PER_THREAD;

    pthread_exit(NULL);
}
