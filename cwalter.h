

typedef struct {
    int port;
    const char *user;
    const char *pem;
    const char **ips;
} cwalter_config;

cwalter_config
cwalter_init_config(
        const char **ips, int port, char *user, char *pem);
