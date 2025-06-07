// sort.h
#ifndef SORT_H
#define SORT_H

void merge(int* array, int left, int mid, int right);
void merge_sort(int* array, int left, int right);
void multi_merge_sort(int* array, int left, int right);
void threadpool_merge_sort(int* array, int size);
void db_merge(int* a, int* b, int left, int mid, int right);

#endif // SORT_H
