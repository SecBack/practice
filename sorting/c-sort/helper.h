// helper.h
#ifndef HELPER_H
#define HELPER_H

struct args {
    int* array;
    int left;
    int right;
};

struct merge_args {
    int* array;
    int left;
    int mid;
    int right;
};

struct db_merge_args {
    int* source;
    int* destination;
    int left;
    int mid;
    int right;
};

int min(int first, int second);
void generate_random_numbers(int* array, int size, int upperBound);
void merge_wrapper(void* merge_args);
void db_merge_wrapper(void* merge_args);
void* merge_sort_wrapper(void* args);
void merge_sort_threadpool_wrapper(void* args);
int min(int first, int second);

#endif // HELPER_H