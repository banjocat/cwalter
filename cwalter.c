#include <libssh2.h>
#include <libssh2_sftp.h>
#include "cwalter.h"


cwalter_config
cwalter_init_config(
                const char **ips, int port, char *user, char *pem) {
        cwalter_config config;
        config.ips = ips;
        config.port = port;
        config.user = user;
        config.pem = pem;
        return config;
}

