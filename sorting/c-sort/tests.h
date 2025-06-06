// tests.h
#ifndef TESTS_H
#define TESTS_H

void generate_random_numbers(int* array, int size, int upperBound);
void test_single_thread(void);
void test_multi_thread(void);
void test_threadpool_merge_sort(void);
void threadpool_merge_sort(int *array, int size);

#endif // TESTS_H