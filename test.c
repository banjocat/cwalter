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
        cwalter_config *config;
        const char * ips[] = { "localhost" };
        config = cwalter_init_config(
                        22, "banjocat",
                        "~/.ssh/id_rsa",
                        ips, 1);
        cwalter_print_config(config);
        mu_assert("port", config->port == 22);
        mu_assert("hostname", !strcmp(config->user, "banjocat"));
        cwalter_free_config(config);
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
