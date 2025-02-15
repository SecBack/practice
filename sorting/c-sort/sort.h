// sort.h
#ifndef SORT_H
#define SORT_H

void merge(int* originalArray, int leftFirstIndex, int leftEndIndex, int rightEndIndex);
void mergeSort(int* toSortArray, int leftFirstIndex, int rightEndIndex);
void multiMergeSort(int* toSortArray, int leftFirstIndex, int rightEndIndex);

#endif // SORT_H