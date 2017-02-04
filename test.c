#include <stdio.h>
#include <string.h>
#include "minunit.h"
#include "cwalter.h"

int tests_run = 0;

static char *test_minunit() {
        mu_assert("minunit failed", 1 == 1);
        return 0;
}

static char *test_configs() {
        cwalter_config config;
        const char * ips[] = { "localhost" };
        config = cwalter_init_config(
                        ips, 22, "banjocat",
                        "~/.ssh/id_rsa");
        mu_assert("hostname", !strcmp(config.user, "banjocat"));
}

static char *all_tests() {
        mu_run_test(test_minunit);
        mu_run_test(test_configs);
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
