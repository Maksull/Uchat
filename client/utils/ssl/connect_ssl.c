#include "../../inc/client.h"

// Establish SSL connection
void connect_ssl(SSL **ssl, int *server_fd, SSL_CTX **ctx)
{
    *ssl = SSL_new(*ctx); // Create a new SSL structure
    SSL_set_mode(*ssl, SSL_MODE_ASYNC); // Set SSL mode to asynchronous
    SSL_set_fd(*ssl, *server_fd); // Associate SSL structure with socket file descriptor

    if (SSL_connect(*ssl) == -1) // Attempt SSL handshake
    {
        handle_error(strerror(errno)); // Handle SSL connection error
        exit(EXIT_FAILURE); // Exit with failure status
    }
}
