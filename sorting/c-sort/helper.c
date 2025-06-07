#include "helper.h"
#include "sort.h"
#include <stdlib.h>

/**
 * @brief wrapper is needed to pass merge to the threadpool
 * 
 * @param args 
 * @return void* 
 */
void merge_wrapper(void* merge_args) {
    struct merge_args* args = (struct merge_args*)merge_args;
    merge(args->array, args->left, args->mid, args->right);
    free(args);
}

/**
 * @brief wrapper is needed to pass merge_sort to the p_thread api
 * 
 * @param args 
 * @return void* 
 */
void* merge_sort_wrapper(void* args) {
    struct args* thread_args = (struct args*)args;
    merge_sort(thread_args->array, thread_args->left, thread_args->right);

    return NULL;
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
 * @brief returns the minimum of 2 values
 * 
 * @param first 
 * @param second 
 * @return int 
 */
int min(int first, int second) {
    if (first < second)
        return first;
    return second;
}