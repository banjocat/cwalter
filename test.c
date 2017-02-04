#include <stdio.h>
#include "minunit.h"
#include "cwalter.h"

int tests_run = 0;

static char *test_minunit() {
        mu_assert("minunit failed", 1 == 1);
        return 0;
}

static char *all_tests() {
        mu_run_test(test_minunit);
        return 0;
}

int main() {
        char *result = all_tests();
        if (result != 0) {
                printf("%s\n", result);
        }
        else {
                printf("All tests passed!\n");
        }
        return result != 0;
}
