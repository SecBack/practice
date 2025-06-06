#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "threadpool.h"

void example_task(void *arg) {
    int *num = (int *)arg;
    printf("Thread %d is working on task %d\n", (int)pthread_self(), *num);
}

int main() {
    threadpool_t *pool = threadpool_create(MAX_THREADS, MAX_QUEUE);

    int tasks[MAX_QUEUE];
    for (int i = 0; i < MAX_QUEUE; i++) {
        tasks[i] = i;
        threadpool_add(pool, example_task, (void *)&tasks[i]);
    }

    sleep(5);
    threadpool_destroy(pool);

    return 0;
}