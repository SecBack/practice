// sort.c
#include <stdlib.h>
#include <pthread.h>
#include "sort.h"

// merges 2 sorted arrays to 1 sorted array, using indicies to save
// memory instead of allocating a 2d array bigger than it needs to be
void merge(int* originalArray, int leftFirstIndex, int leftEndIndex, int rightEndIndex) {
    // find the sizes of both arrays
    int leftSize = leftEndIndex - leftFirstIndex + 1;
    int rightSize = rightEndIndex - leftEndIndex;

    // since we want to change the original array, we need keep track of left and right
    int* leftArray = (int*)malloc(leftSize * sizeof(int));
    int* rightArray = (int*)malloc(rightSize * sizeof(int));

    for (int i = 0; i < leftSize; i++)
        leftArray[i] = originalArray[leftFirstIndex + i];
    for (int i =  0; i < rightSize; i++) 
        rightArray[i] = originalArray[leftEndIndex + 1 + i];

    // from the sorted left and right arrays, add lowest number to the merged array
    int i = 0, j = 0, k = leftFirstIndex;
    while (i < leftSize && j < rightSize) {
        if (leftArray[i] <= rightArray[j]) {
            originalArray[k] = leftArray[i];
            i++;
        } else {
            originalArray[k] = rightArray[j];
            j++;
        }
        k++;
    }

    // in case there ends up being leftovers in either the left or right array
    while (i < leftSize) {
        originalArray[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < rightSize) {
        originalArray[k] = rightArray[j];
        j++;
        k++;
    }

    // free the pointers created earlier
    free(leftArray);
    free(rightArray);
}

// recursevily split the given array to smaller arrays until size 1, then
// then take 2 elements and merge into one sorted array, then sort 2 arrays 
// of 2 elements by merging them to one sorted array, repeat until done
void mergeSort(int* toSortArray, int leftFirstIndex, int rightEndIndex) {
    // base condition, continue splitting until arrays are size 1
    if (leftFirstIndex < rightEndIndex) {
        // find the middle index to split the array in half
        int leftEndIndex = leftFirstIndex + (rightEndIndex - leftFirstIndex) / 2;

        mergeSort(toSortArray, leftFirstIndex, leftEndIndex);
        mergeSort(toSortArray, leftEndIndex + 1, rightEndIndex);

        merge(toSortArray, leftFirstIndex, leftEndIndex, rightEndIndex);
    }
}

void multiMerge() {
   
}

struct args {
    int* toSortArray;
    int leftFirstIndex;
    int rightEndIndex;
};

void* mergeSortWrapper(void* args) {
    struct args* threadArgs = (struct args*)args;
    mergeSort(threadArgs->toSortArray, threadArgs->leftFirstIndex, threadArgs->rightEndIndex);
    return NULL;
}

// first iteration:
// a thread for the first 2 halves
void multiMergeSort(int* toSortArray, int leftFirstIndex, int rightEndIndex) {
    int leftEndIndex = leftFirstIndex + (rightEndIndex - leftFirstIndex) / 2;

    struct args *leftThreadArgs = (struct args *)malloc(sizeof(struct args));
    struct args *rightThreadArgs = (struct args *)malloc(sizeof(struct args));

    leftThreadArgs->toSortArray = toSortArray;
    leftThreadArgs->leftFirstIndex = leftFirstIndex;
    leftThreadArgs->rightEndIndex = leftEndIndex;
    rightThreadArgs->toSortArray = toSortArray;
    rightThreadArgs->leftFirstIndex = leftEndIndex + 1;
    rightThreadArgs->rightEndIndex = rightEndIndex;

    pthread_t leftThread;
    pthread_t rightThread;

    pthread_create(&leftThread, NULL, mergeSortWrapper, (void *)leftThreadArgs);
    pthread_create(&rightThread, NULL, mergeSortWrapper, (void *)rightThreadArgs);
    pthread_join(leftThread, NULL);
    pthread_join(rightThread, NULL);

    free(leftThreadArgs);
    free(rightThreadArgs);
}