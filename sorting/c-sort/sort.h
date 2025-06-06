// sort.h
#ifndef SORT_H
#define SORT_H

struct args {
    int* to_sort_array;
    int left_first_index;
    int right_end_index;
};

void merge(int* original_array, int left_first_index, int left_end_index, int right_end_index);
void merge_sort(int* toSort_array, int left_first_index, int right_end_index);
void multi_merge_sort(int* to_sort_array, int left_first_index, int right_end_index);
void threadpool_merge_sort(int* array, int size);


#endif // SORT_H
