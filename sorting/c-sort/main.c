#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include "tests.h"

int main() {
    testSingleThread();
    testMultiThread();

    return 0;
}