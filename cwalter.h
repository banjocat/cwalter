

typedef struct {
    int port;
    char *user;
    char *pem;
    char **ips;
    int ips_length;
} cwalter_config;

cwalter_config *cwalter_init_config(
        int port, char *user, char *pem,
        const char **ips, size_t ips_len);

int cwalter_free_config(cwalter_config *config);

void cwalter_print_config(cwalter_config *config);

