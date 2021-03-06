#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <libssh/libssh.h>

#include "cwalter.h"


static char *create_string(const char *str);
static cwalter_config *cwalter_config_new(
        int port, char *user, char *pem,
        const char **ips, size_t ips_len);

static int cwalter_config_free(cwalter_config *config);

cwalter_session *cwalter_session_new(
        int port, char *user, char *pem,
        const char **ips, size_t ips_len)
{
        assert(user && pem && ips);
        assert(ips_len > 0);
        cwalter_session *session = malloc(sizeof(cwalter_session));
        session->config = cwalter_config_new(
                        port, user, pem, ips, ips_len);
        session->session_length = ips_len;
        ssh_session *sessions = malloc(sizeof(ssh_session) * ips_len);
        for (int i = 0; i < ips_len; i++) {
                sessions[i] = ssh_new();
                assert(sessions[i]);
                ssh_options_set(sessions[i], SSH_OPTIONS_HOST, ips[i]);
                ssh_options_set(sessions[i], SSH_OPTIONS_PORT, &port);
        }
        session->sessions = sessions;
        return session;
}

int cwalter_session_free(cwalter_session *session)
{
        cwalter_config_free(session->config);
        for (int i = 0; i < session->session_length; i++) {
                ssh_free(session->sessions[i]);
        }
        free(session->sessions);
        free(session);
        return 0;
}

int cwalter_session_connect(cwalter_session *session)
{
        for (int i = 0; i < session->session_length; i++) {
                int rc = ssh_connect(session->sessions[i]);
                int state = ssh_is_server_known(session->sessions[i]);
                if (state == SSH_SERVER_NOT_KNOWN ||
                                state == SSH_SERVER_FILE_NOT_FOUND) {
                        ssh_write_knownhost(session->sessions[i]);
                }
        }
        return 0;
}

int cwalter_session_disconnect(cwalter_session *session)
{
        for (int i = 0; i < session->session_length; i++) {
                ssh_disconnect(session->sessions[i]);
        }
        return 0;
}

cwalter_config *cwalter_config_new(
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


int cwalter_config_free(cwalter_config *config)
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

/*
 * mallocs parameter and returns point
 */
char* create_string(const char *str)
{
        int len = strlen(str) + 1;
        char *string = malloc(len * sizeof(char));
        strcpy(string, str);
        return string;
}

