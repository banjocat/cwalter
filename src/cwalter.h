#include <libssh/libssh.h>


typedef struct {
    int port;
    char *user;
    char *pem;
    char **ips;
    int ips_length;
} cwalter_config;

typedef struct {
    cwalter_config *config;
    ssh_session *sessions;
    int session_length;
} cwalter_session;

cwalter_session *cwalter_session_new(
        int port, char *user, char *pem,
        const char **ips, size_t ips_len);

int cwalter_session_free(cwalter_session *cwalter_session);

int cwalter_session_connect(cwalter_session *session);


void cwalter_print_config(cwalter_config *config);
