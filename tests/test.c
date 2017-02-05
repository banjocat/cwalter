#include <stdio.h>
#include <string.h>
#include "minunit.h"
#include "cwalter.h"

int tests_run = 0;

static cwalter_session *setup() {
        cwalter_session *session;
        const char * ips[] = { "localhost" };
        session = cwalter_session_new(
                        22, "banjocat",
                        "~/.ssh/id_rsa",
                        ips, 1);
        return session;
}

static char *test_minunit() {
        mu_assert("minunit failed", 1 == 1);
        return 0;
}


static char *test_configs() {
        cwalter_session *session = setup();
        cwalter_config *config = session->config;
        mu_assert("port", config->port == 22);
        mu_assert("hostname", !strcmp(config->user, "banjocat"));
        cwalter_session_free(session);
}

static char *test_connect() {
        cwalter_session *session = setup();
        int connect = cwalter_session_connect(session);
        mu_assert("connect", connect == 0);
        mu_assert("session_length", session->session_length == 1);
        for (int i = 0; i < session->session_length; i++) {
                int status = ssh_get_status(session->sessions[i]);
                mu_assert("status", ssh_get_status(session->sessions[i]) == 0);
        }
        cwalter_session_free(session);
}


static char *all_tests() {
        mu_run_test(test_minunit);
        mu_run_test(test_configs);
        mu_run_test(test_connect);
        return 0;
}

int main() {
        char *result = all_tests();
        if (result != 0) {
                printf("TEST FAILED!\n");
                printf("%s\n", result);
        }
        else {
                printf("All tests passed!\n");
        }
        return result != 0;
}
