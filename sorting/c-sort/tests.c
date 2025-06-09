#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

/**
 * @brief given an array, fill with random numbers until the length is equal
 * to size, each number will not be bigger than upper bound
 * 
 * @param array array to fill
 * @param size size of the array
 * @param upper_bound max generated number
 */
void generate_random_numbers(int* array, int size, int upper_bound) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < size; i++) {
        array[i] = rand() % upper_bound + 1;
    }
}

/**
 * @brief tests my single threaded merge sort implementation
 * 
 */
void test_single_thread(void) {
    printf("single threaded:\n");

    const int size1 = 1;
    const int size2 = 10;
    const int size3 = 100;
    const int size4 = 1000;
    const int size5 = 10000000;
    int* numbers1 = (int*)malloc(size1 * sizeof(int));
    int* numbers2 = (int*)malloc(size2 * sizeof(int));
    int* numbers3 = (int*)malloc(size3 * sizeof(int));
    int* numbers4 = (int*)malloc(size4 * sizeof(int));
    int* numbers5 = (int*)malloc(size5 * sizeof(int));
    generate_random_numbers(numbers1, size1, 1000);
    generate_random_numbers(numbers2, size2, 2000);
    generate_random_numbers(numbers3, size3, 5000);
    generate_random_numbers(numbers4, size4, 50000);
    generate_random_numbers(numbers5, size5, 1000000);

    // Measure time for sorting numbers1
    clock_t start = clock();
    merge_sort(numbers1, 0, size1 - 1);
    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken to sort %d numbers: %.6f seconds\n", size1, time_taken);

    // Measure time for sorting numbers1
    start = clock();
    merge_sort(numbers2, 0, size2 - 1);
    end = clock();
    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken to sort %d numbers: %.6f seconds\n", size2, time_taken);

    // Measure time for sorting numbers1
    start = clock();
    merge_sort(numbers3, 0, size3 - 1);
    end = clock();
    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken to sort %d numbers: %.6f seconds\n", size3, time_taken);

    // Measure time for sorting numbers1
    start = clock();
    merge_sort(numbers4, 0, size4 - 1);
    end = clock();
    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken to sort %d numbers: %.6f seconds\n", size4, time_taken);

    // Measure time for sorting numbers1
    start = clock();
    merge_sort(numbers5, 0, size5 - 1);
    end = clock();
    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken to sort %d numbers: %.6f seconds\n", size5, time_taken);

    printf("\n");

    free(numbers1);
    free(numbers2);
    free(numbers3);
    free(numbers4);
    free(numbers5);
}

/**
 * @brief tests my multi threaded merge sort implementation
 * 
 */
void test_multi_thread(void) {
    printf("multi threaded:\n");

    const int size1 = 1;
    const int size2 = 10;
    const int size3 = 100;
    const int size4 = 1000;
    const int size5 = 250000000;
    int* numbers1 = (int*)malloc(size1 * sizeof(int));
    int* numbers2 = (int*)malloc(size2 * sizeof(int));
    int* numbers3 = (int*)malloc(size3 * sizeof(int));
    int* numbers4 = (int*)malloc(size4 * sizeof(int));
    int* numbers5 = (int*)malloc(size5 * sizeof(int));
    generate_random_numbers(numbers1, size1, 100);
    generate_random_numbers(numbers2, size2, 100);
    generate_random_numbers(numbers3, size3, 100);
    generate_random_numbers(numbers4, size4, 100);
    generate_random_numbers(numbers5, size5, 100);

    // Measure time for sorting numbers1
    clock_t start = clock();
    multi_merge_sort(numbers1, 0, size1 - 1);
    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken to sort %d numbers: %.6f seconds\n", size1, time_taken);

    // Measure time for sorting numbers1
    start = clock();
    multi_merge_sort(numbers2, 0, size2 - 1);
    end = clock();
    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken to sort %d numbers: %.6f seconds\n", size2, time_taken);

    // Measure time for sorting numbers1
    start = clock();
    multi_merge_sort(numbers3, 0, size3 - 1);
    end = clock();
    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken to sort %d numbers: %.6f seconds\n", size3, time_taken);

    // Measure time for sorting numbers1
    start = clock();
    multi_merge_sort(numbers4, 0, size4 - 1);
    end = clock();
    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken to sort %d numbers: %.6f seconds\n", size4, time_taken);

    // Measure time for sorting numbers1
    start = clock();
    multi_merge_sort(numbers5, 0, size5 - 1);
    end = clock();
    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken to sort %d numbers: %.6f seconds\n", size5, time_taken);

    printf("\n");

    free(numbers1);
    free(numbers2);
    free(numbers3);
    free(numbers4);
    free(numbers5);
}

/**
 * @brief tests my multi threaded merge sort implementation
 * 
 */
void test_threadpool_merge_sort(void) {
    printf("threadpool:\n");

    const int size1 = 4;
    const int size2 = 10;
    const int size3 = 100;
    const int size4 = 1000;
    const int size5 = 25000000;
    int* numbers1 = (int*)malloc(size1 * sizeof(int));
    int* numbers2 = (int*)malloc(size2 * sizeof(int));
    int* numbers3 = (int*)malloc(size3 * sizeof(int));
    int* numbers4 = (int*)malloc(size4 * sizeof(int));
    int* numbers5 = (int*)malloc(size5 * sizeof(int));
    generate_random_numbers(numbers1, size1, 100);
    generate_random_numbers(numbers2, size2, 100);
    generate_random_numbers(numbers3, size3, 100);
    generate_random_numbers(numbers4, size4, 100);
    generate_random_numbers(numbers5, size5, 100);

    // Measure time for sorting numbers1
    clock_t start = clock();
    threadpool_merge_sort(numbers1, size1);
    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken to sort %d numbers: %.6f seconds\n", size1, time_taken);

    // Measure time for sorting numbers1
    start = clock();
    threadpool_merge_sort(numbers2, size2);
    end = clock();
    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken to sort %d numbers: %.6f seconds\n", size2, time_taken);

    // Measure time for sorting numbers1
    start = clock();
    threadpool_merge_sort(numbers3, size3);
    end = clock();
    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken to sort %d numbers: %.6f seconds\n", size3, time_taken);

    // // Measure time for sorting numbers1
    start = clock();
    threadpool_merge_sort(numbers4, size4);
    end = clock();
    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken to sort %d numbers: %.6f seconds\n", size4, time_taken);

    // Measure time for sorting numbers1
    start = clock();
    threadpool_merge_sort(numbers5, size5);
    end = clock();
    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken to sort %d numbers: %.6f seconds\n", size5, time_taken);

    free(numbers1);
    free(numbers2);
    free(numbers3);
    free(numbers4);
    free(numbers5);
}
