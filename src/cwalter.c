#include <stdio.h>
#include <stdlib.h>
#include <libssh2.h>
#include <libssh2_sftp.h>
#include "cwalter.h"

static char *create_string(const char *str);


cwalter_config *cwalter_init_config(
                int port, char *user, char *pem,
                const char **ips, size_t ips_len)
{
        cwalter_config *config = malloc(sizeof(cwalter_config));
        config->port = port;
        config->ips_length = ips_len;
        config->user = create_string(user);
        config->pem = create_string(pem);
        config->ips = malloc(ips_len * sizeof(char*));
        for (int i = 0; i < ips_len; i++) {
                config->ips[i] = create_string(ips[i]);
        }
        return config;
}

int cwalter_free_config(cwalter_config *config)
{
        free(config->user);
        free(config->pem);
        for (int i = 0; i < config->ips_length; i++) {
                free(config->ips[i]);
        }
        free(config->ips);
        free(config);
        return 0;
}



void cwalter_print_config(cwalter_config *config)
{
        printf("IPS:\n");
        for (int i = 0; i < config->ips_length; i++) {
                printf("%s\n", config->ips[i]);
        }
        printf("port: %d, user: %s, pem: %s\n",
                        config->port, config->user, config->pem);
}

char* create_string(const char *str)
{
        int len = strlen(str) + 1;
        char *string = malloc(len * sizeof(char));
        strcpy(string, str);
        return string;
}
