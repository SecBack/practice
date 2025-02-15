#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

// given an array, fill with random numbers until the length is equal
// to size, each number will not be bigger than upper bound
void generateRandomNumbers(int* array, int size, int upperBound) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        array[i] = rand() % upperBound + 1;
    }
}

// tests my single threaded merge sort implementation
void testSingleThread() {
    printf("single threaded:\n");

    const int size1 = 1000;
    const int size2 = 2000;
    const int size3 = 5000;
    const int size4 = 50000;
    const int size5 = 1000000;
    int numbers1[size1];
    int numbers2[size2];
    int numbers3[size3];
    int numbers4[size4];
    int numbers5[size5];
    generateRandomNumbers(numbers1, size1, 1000);
    generateRandomNumbers(numbers2, size2, 2000);
    generateRandomNumbers(numbers3, size3, 5000);
    generateRandomNumbers(numbers4, size4, 50000);
    generateRandomNumbers(numbers5, size5, 1000000);

    // Measure time for sorting numbers1
    clock_t start = clock();
    mergeSort(numbers1, 0, size1 - 1);
    clock_t end = clock();
    double timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken to sort %d numbers: %.6f seconds\n", size1, timeTaken);

    // Measure time for sorting numbers1
    start = clock();
    mergeSort(numbers2, 0, size2 - 1);
    end = clock();
    timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken to sort %d numbers: %.6f seconds\n", size2, timeTaken);

    // Measure time for sorting numbers1
    start = clock();
    mergeSort(numbers3, 0, size3 - 1);
    end = clock();
    timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken to sort %d numbers: %.6f seconds\n", size3, timeTaken);

    // Measure time for sorting numbers1
    start = clock();
    mergeSort(numbers4, 0, size4 - 1);
    end = clock();
    timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken to sort %d numbers: %.6f seconds\n", size4, timeTaken);

    // Measure time for sorting numbers1
    start = clock();
    mergeSort(numbers5, 0, size5 - 1);
    end = clock();
    timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken to sort %d numbers: %.6f seconds\n", size5, timeTaken);

    printf("\n");
}

// tests my multi threaded merge sort implementation
void testMultiThread() {
    printf("multi threaded:\n");

    const int size1 = 1000;
    const int size2 = 2000;
    const int size3 = 5000;
    const int size4 = 50000;
    const int size5 = 1000000;
    int numbers1[size1];
    int numbers2[size2];
    int numbers3[size3];
    int numbers4[size4];
    int numbers5[size5];
    generateRandomNumbers(numbers1, size1, 1000);
    generateRandomNumbers(numbers2, size2, 2000);
    generateRandomNumbers(numbers3, size3, 5000);
    generateRandomNumbers(numbers4, size4, 50000);
    generateRandomNumbers(numbers5, size5, 1000000);

    // Measure time for sorting numbers1
    clock_t start = clock();
    multiMergeSort(numbers1, 0, size1 - 1);
    clock_t end = clock();
    double timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken to sort %d numbers: %.6f seconds\n", size1, timeTaken);

    // Measure time for sorting numbers1
    start = clock();
    multiMergeSort(numbers2, 0, size2 - 1);
    end = clock();
    timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken to sort %d numbers: %.6f seconds\n", size2, timeTaken);

    // Measure time for sorting numbers1
    start = clock();
    multiMergeSort(numbers3, 0, size3 - 1);
    end = clock();
    timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken to sort %d numbers: %.6f seconds\n", size3, timeTaken);

    // Measure time for sorting numbers1
    start = clock();
    multiMergeSort(numbers4, 0, size4 - 1);
    end = clock();
    timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken to sort %d numbers: %.6f seconds\n", size4, timeTaken);

    // Measure time for sorting numbers1
    start = clock();
    multiMergeSort(numbers5, 0, size5 - 1);
    end = clock();
    timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken to sort %d numbers: %.6f seconds\n", size5, timeTaken);
}