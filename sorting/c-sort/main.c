#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "tests.h"

int main(void) {
    test_single_thread();
    test_multi_thread();
    test_threadpool_merge_sort();

    return 0;
}
