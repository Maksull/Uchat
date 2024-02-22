#ifndef SERVER_HEADER
#define SERVER_HEADER

#include "../../libraries/libmx/inc/libmx.h"

#include "../../libraries/openssl/openssl/ssl.h"
#include "../../libraries/openssl/openssl/err.h"

// SERVER UTILS

void init_daemon();
void handle_cli_arg_errors(char** argv);
int init_server_socket(struct sockaddr* server_address, socklen_t address_size);
void create_new_client(SSL* ssl, int client_socket);
void handle_error(const char* error);

#endif