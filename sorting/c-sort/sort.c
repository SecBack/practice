#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include "sort.h"
#include "helper.h"
#include "./../../threadpool/threadpool.h"

/**
 * @brief merges 2 sorted arrays to 1 sorted array, using indicies to save
 * memory instead of allocating a 2d array bigger than it needs to be
 * 
 * @param array the array to be sorted
 * @param left index of first element in the first array
 * @param mid index of last element in the first array
 * @param right index of last element in the last array
 */
void merge(int* array, int left, int mid, int right) {
    // find the sizes of both arrays
    int left_size = mid - left + 1;
    int right_size = right - mid;

    // since we want to change the original array, we need keep track of left and right
    int* tmp_left = (int*)malloc((size_t)left_size * sizeof(int));
    int* tmp_right = (int*)malloc((size_t)right_size * sizeof(int));

    for (int i = 0; i < left_size; i++)
        tmp_left[i] = array[left + i];
    for (int i =  0; i < right_size; i++) 
        tmp_right[i] = array[mid + 1 + i];

    // from the sorted left and right arrays, add lowest number to the merged array
    int i = 0, j = 0, k = left;
    while (i < left_size && j < right_size) {
        if (tmp_left[i] <= tmp_right[j]) {
            array[k] = tmp_left[i];
            i++;
        } else {
            array[k] = tmp_right[j];
            j++;
        }
        k++;
    }

    // in case there ends up being leftovers in either the left or right array
    while (i < left_size) {
        array[k] = tmp_left[i];
        i++;
        k++;
    }

    while (j < right_size) {
        array[k] = tmp_right[j];
        j++;
        k++;
    }
    
    // free the pointers created earlier
    free(tmp_left);
    free(tmp_right);
}

/**
 * @brief double buffering. instead of overwriting the same array all the time
 * we "ping pong" between 2 arrays
 * 
 * @param a ping
 * @param b pong
 * @param left index of first element in left array
 * @param mid index of last element in left array
 * @param right index of last element in right array
 */
void db_merge(int* source, int* destination, int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;
    
    while (i <= mid && j <= right) {
        if (source[i] <= source[j]) destination[k++] = source[i++];
        else destination[k++] = source[j++];
    }
    while (i <= mid) destination[k++] = source[i++];
    while (j <= right) destination[k++] = source[j++];
}

/**
 * @brief recursevily split the given array to smaller arrays until size 1, then
 * then take 2 elements and merge into one sorted array, then sort 2 arrays
 * of 2 elements by merging them to one sorted array, repeat until done
 * 
 * @param array array to be sorted
 * @param left index of first element in first array
 * @param right index of last element in last array
 */
void merge_sort(int* array, int left, int right) {
    //printf("merge sort: left=%d, right=%d\n", left_first_index, right_end_index);
    // base condition, continue splitting until arrays are size 1
    if (left < right) {
        // find the middle index to split the array in half
        int mid = left + (right - left) / 2;

        merge_sort(array, left, mid);
        merge_sort(array, mid + 1, right);

        merge(array, left, mid, right);
    }
}

/**
 * @brief merge sort with 2 threads
 * 
 * @param array the array to sort
 * @param left index of first element in the first array
 * @param right index of last element in the last array
 */
void multi_merge_sort(int* array, int left, int right) {
    int left_end_index = left + (right - left) / 2;

    struct args *left_thread_args = (struct args *)malloc(sizeof(struct args));
    left_thread_args->array = array;
    left_thread_args->left = left;
    left_thread_args->right = left_end_index;

    // left side done by new thread, right side done by main thread
    pthread_t left_thread;
    pthread_create(&left_thread, NULL, merge_sort_wrapper, (void *)left_thread_args);
    merge_sort(array, left_end_index + 1, right);

    // main thread waits for the other thread
    pthread_join(left_thread, NULL);

    // merge the 2 sorted halves
    merge(array, left, left_end_index, right);
    free(left_thread_args);
}

/**
 * @brief distributes the work using a threadpool
 * 
 * @param array to sort array
 * @param left index of first element in left array
 * @param right index of last element in right array
 */
void threadpool_merge_sort(int* array, int size) {
    threadpool_t* pool = threadpool_create(MAX_THREADS, MAX_QUEUE);
    int* aux = malloc(size * sizeof(int));
    int* source = array;
    int* destination = aux;

    for (int sub_size = 1; sub_size < size; sub_size *= 2) {
        for (int sub_index = 0; sub_index < size - sub_size; sub_index += 2*sub_size) {
            int left = sub_index;
            int mid = min(sub_index + sub_size - 1, size - 1);
            int right = min(sub_index + 2*sub_size - 1, size - 1);

            // if subarrays are small merge single threaded
            if (sub_size < 1000000) {
                merge(array, left, mid, right);
            } else {
                struct db_merge_args *db_merge_args = (struct db_merge_args *)malloc(sizeof(struct merge_args));
                db_merge_args->source = array;
                db_merge_args->destination = destination;
                db_merge_args->left = left;
                db_merge_args->mid = mid;
                db_merge_args->right = right;
                threadpool_add(pool, db_merge_wrapper, db_merge_args);
            }

        }
        threadpool_wait(pool);
        // Swap src and dest for next layer
        int* tmp = source; source = destination; destination = tmp;
    }

    // If the sorted data is not in the original array, copy it back
    if (source != array) {
        memcpy(array, aux, size * sizeof(int));
    }
    free(aux);

    // clean up
    threadpool_destroy(pool);
}
