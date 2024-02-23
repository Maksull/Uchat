#ifndef SERVER_HEADER
#define SERVER_HEADER

#include "../../libraries/libmx/inc/libmx.h"

#include "../../libraries/openssl/openssl/ssl.h"
#include "../../libraries/openssl/openssl/err.h"

#include "../../libraries/cjson/inc/cJSON.h"

typedef struct s_user
{
    // TODO
} t_user;

typedef struct s_server_utils
{
    int client_socket;
    SSL *ssl;
    t_user *user;
} t_server_utils;

// SERVER UTILS

void init_daemon();
void init_ssl(SSL_CTX **ctx);
void load_ssl_sertificate(SSL_CTX *ctx, const char *cert, const char *key);
void handle_cli_arg_errors(char **argv);
int init_server_socket(struct sockaddr *server_address, socklen_t address_size);
void create_new_client(SSL *ssl, int client_socket);
void handle_error(const char *err);

// THREADS

void *thread_handler(void *arg);

#endif