#include <stdlib.h>
#include "threadpool.h"

/**
 * @brief declearing the funciton here so it cant be  called from the outside
 * the actual function @ref threadpool_thread
 * 
 * @param threadpool 
 * @return void* 
 */
static void *threadpool_thread(void *threadpool);

/**
 * @brief creates the threadpool with the variables set in the header file
 * apparently all thread related functions, and malloc can fail, but
 * if it dies, it dies... @ref *threadpool_thread(void *threadpool);
 * 
 * @param thread_count 
 * @param queue_size 
 * @return threadpool_t* 
 */
threadpool_t *threadpool_create(int thread_count, int queue_size) {
    // allocate memory for the threadpool itself
    threadpool_t *pool = (threadpool_t*)malloc(sizeof(threadpool_t));

    // set all the values of the pool
    pool->thread_count = thread_count;
    pool->queue_size = queue_size;
    pool->head = pool->tail = pool->count = 0;
    pool->shutdown = 0;

    // allocate memory for the threads and the queue
    pool->threads = (pthread_t*)malloc(thread_count * sizeof(pthread_t));
    pool->queue = (threadpool_task_t*)malloc(queue_size * sizeof(threadpool_task_t));

    // 
    pthread_mutex_init(&(pool->lock), NULL);
    pthread_cond_init(&(pool->notify), NULL);

    // create the threads
    for (int i = 0; i < thread_count; i++) {
        pthread_create(&(pool->threads[i]), NULL, threadpool_thread, (void*)pool);
    }
    
    return pool;
}

/**
 * @brief add a task to the pool queue
 * 
 * @param pool a living threadpool
 * @param function 
 * @param argument 
 * @return int 
 */
int threadpool_add(threadpool_t *pool, void (*function)(void *), void *argument) {
    int next;
    
    // if the pool or the function is null, return
    if (pool == NULL || function == NULL) {
        return -1;
    }

    // lock the queue while we're working with it
    pthread_mutex_lock(&(pool->lock));

    // incrementing the pool size, terminate if max queue is reached
    // modulus wrap around 
    next = (pool->tail + 1) % pool->queue_size;
    if (pool->count == pool->queue_size) {
        pthread_mutex_unlock(&(pool->lock));
        return -1;
    }

    // pass the funciton and arguments to the task
    pool->queue[pool->tail].fucntion = function;
    pool->queue[pool->tail].argument = argument;
    pool->tail = next;
    pool->count += 1;

    // notify the threads that there is a new task
    pthread_cond_signal(&(pool->notify));
    pthread_mutex_unlock(&(pool->lock));

    return 0;
}

/**
 * @brief makes sure no one can use the pool and frees the memory, normally the pool is
 * kept alive for the duration of the program
 * 
 * @param pool 
 * @return int 
 */
int threadpool_destroy(threadpool_t *pool) {
    if (pool == NULL) 
        return -1;

    // lock pool, making sure no one else is using it
    pthread_mutex_lock(&(pool->lock));

    pool->shutdown = 1;

    // wake up the threads so they can see the shutdown flag
    pthread_cond_broadcast(&(pool->notify));
    pthread_mutex_unlock(&(pool->lock));

    // join all threads to stop them from cycling
    for (int i = 0; i < pool->thread_count; i++) 
        pthread_join(pool->threads[i], NULL);

    // destroy the mutex and condition variables
    pthread_mutex_destroy(&(pool->lock));
    pthread_cond_destroy(&(pool->notify));

    // free up the allocated memory
    free(pool->threads);
    free(pool->queue);
    free(pool);

    return 0;
}

/**
 * @brief this is where the threads sleep at night, until there
 * is work to do
 * 
 * @param threadpool 
 * @return void* 
 */
static void *threadpool_thread(void *threadpool) {
    threadpool_t *pool = (threadpool_t*)threadpool;
    threadpool_task_t task;

    // infinite loop to keep the threads alive
    for (;;) {
        // unlock the mutex as we might be about to do work
        pthread_mutex_lock(&(pool->lock));

        // if there is nothing in the queue, but the pool hasen't been
        // terminated, wait for a new task in the queue
        while((pool->count == 0) && (!pool->shutdown)) {
            pthread_cond_wait(&(pool->notify), &(pool->lock));
        }

        // if the pool has been terminated and there is nothing
        // in the queue, kill thread
        if ((pool->shutdown) && (pool->count == 0)) {
            pthread_mutex_unlock(&(pool->lock));
            pthread_exit(NULL);
        }

        // get the function and arguments for the task, increment the 
        // pool head and decrement the pool counter
        task.fucntion = pool->queue[pool->head].fucntion;
        task.argument = pool->queue[pool->head].argument;
        pool->head = (pool->head + 1) % pool->queue_size;
        pool->count -= 1;

        // unlock the mutex and execute the work of the task
        pthread_mutex_unlock(&(pool->lock));
        // this calls the function with the arguments, programatically
        (*(task.fucntion))(task.argument);
    }
}