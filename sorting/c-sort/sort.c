// sort.c
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "sort.h"
#include "./../../threadpool/threadpool.h"

/**
 * @brief merges 2 sorted arrays to 1 sorted array, using indicies to save
 * memory instead of allocating a 2d array bigger than it needs to be
 * 
 * @param original_array the array to be sorted
 * @param left_first_index index of first element in the first array
 * @param left_end_index index of last element in the first array
 * @param right_end_index index of last element in the last array
 */
void merge(int* original_array, int left_first_index, int left_end_index, int right_end_index) {
    // find the sizes of both arrays
    int left_size = left_end_index - left_first_index + 1;
    int right_size = right_end_index - left_end_index;

    // since we want to change the original array, we need keep track of left and right
    int* left_array = (int*)malloc((size_t)left_size * sizeof(int));
    int* right_array = (int*)malloc((size_t)right_size * sizeof(int));

    for (int i = 0; i < left_size; i++)
        left_array[i] = original_array[left_first_index + i];
    for (int i =  0; i < right_size; i++) 
        right_array[i] = original_array[left_end_index + 1 + i];

    // from the sorted left and right arrays, add lowest number to the merged array
    int i = 0, j = 0, k = left_first_index;
    while (i < left_size && j < right_size) {
        if (left_array[i] <= right_array[j]) {
            original_array[k] = left_array[i];
            i++;
        } else {
            original_array[k] = right_array[j];
            j++;
        }
        k++;
    }

    // in case there ends up being leftovers in either the left or right array
    while (i < left_size) {
        original_array[k] = left_array[i];
        i++;
        k++;
    }

    while (j < right_size) {
        original_array[k] = right_array[j];
        j++;
        k++;
    }
    
    // free the pointers created earlier
    free(left_array);
    free(right_array);
}

/**
 * @brief recursevily split the given array to smaller arrays until size 1, then
 * then take 2 elements and merge into one sorted array, then sort 2 arrays
 * of 2 elements by merging them to one sorted array, repeat until done
 * 
 * @param to_sort_array array to be sorted
 * @param left_first_index index of first element in first array
 * @param right_end_index index of last element in last array
 */
void merge_sort(int* to_sort_array, int left_first_index, int right_end_index) {
    //printf("merge sort: left=%d, right=%d\n", left_first_index, right_end_index);
    // base condition, continue splitting until arrays are size 1
    if (left_first_index < right_end_index) {
        // find the middle index to split the array in half
        int left_end_index = left_first_index + (right_end_index - left_first_index) / 2;

        merge_sort(to_sort_array, left_first_index, left_end_index);
        merge_sort(to_sort_array, left_end_index + 1, right_end_index);

        merge(to_sort_array, left_first_index, left_end_index, right_end_index);
    }
}

/**
 * @brief wrapper is needed to pass merge_sort to the p_thread api
 * 
 * @param args 
 * @return void* 
 */
void* merge_sort_wrapper(void* args) {
    struct args* thread_args = (struct args*)args;
    merge_sort(thread_args->to_sort_array, thread_args->left_first_index, thread_args->right_end_index);

    return NULL;
}

/**
 * @brief merge sort with 2 threads
 * 
 * @param to_sort_array the array to sort
 * @param left_first_index index of first element in the first array
 * @param right_end_index index of last element in the last array
 */
void multi_merge_sort(int* to_sort_array, int left_first_index, int right_end_index) {
    int left_end_index = left_first_index + (right_end_index - left_first_index) / 2;

    struct args *left_thread_args = (struct args *)malloc(sizeof(struct args));
    left_thread_args->to_sort_array = to_sort_array;
    left_thread_args->left_first_index = left_first_index;
    left_thread_args->right_end_index = left_end_index;

    // left side done by new thread, right side done by main thread
    pthread_t left_thread;
    pthread_create(&left_thread, NULL, merge_sort_wrapper, (void *)left_thread_args);
    merge_sort(to_sort_array, left_end_index + 1, right_end_index);

    // main thread waits for the other thread
    pthread_join(left_thread, NULL);

    // merge the 2 sorted halves
    merge(to_sort_array, left_first_index, left_end_index, right_end_index);
    free(left_thread_args);
}

/**
 * @brief needed because the p_threads library expects this funciton signature
 * 
 * @param args 
 */
void merge_sort_threadpool_wrapper(void* args) {
    merge_sort_wrapper(args);
}

/**
 * @brief distributes the work using a threadpool
 * 
 * @param array to sort array
 * @param size size of the array
 */
void threadpool_merge_sort(int* array, int size) {
    struct args *args = (struct args *)malloc(sizeof(struct args));
    args->to_sort_array = array;
    int sub_size = size / MAX_THREADS;

    // create the pool
    threadpool_t* pool = threadpool_create(MAX_THREADS, MAX_QUEUE);

    // split the array into sub arrays of size MAX_THREADS
    int index_buffer = 1;
    for (int i = 0; i < size; i += sub_size) {


        args->left_first_index = i;
        args->right_end_index = i + sub_size;

        if (i == 0) {
            i += index_buffer;
        }

        threadpool_add(pool, merge_sort_threadpool_wrapper, args);
    }

    //merge(array, 0,);

    // clean up
    threadpool_destroy(pool);
    free(args);

    // use threadpool to do the final merge somehow, reqs multithreading the merge function, which sould be a different function
    // because we dont want each thread to spawn new threads
}
