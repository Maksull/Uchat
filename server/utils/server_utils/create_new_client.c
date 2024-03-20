#include "../../inc/server.h"

static void accept_ssl_connection(SSL *ssl)
{
    // Accept SSL connection
    if (SSL_accept(ssl) == -1)
    {
        handle_error(strerror(errno));
        exit(EXIT_FAILURE);
    }
}

static void set_socket_non_blocking(int client_socket)
{
    // Set client socket to non-blocking mode
    int flags = fcntl(client_socket, F_GETFL, 0);
    if (flags == -1)
    {
        logger(strerror(errno), ERROR_LOG);
    }

    fcntl(client_socket, F_SETFL, flags | O_NONBLOCK); // Set socket to non-blocking mode
    fcntl(client_socket, F_SETFD, O_NONBLOCK);         // Set socket file descriptor to non-blocking mode
}

static t_server_utils *initialize_server_utils(SSL *ssl, int client_socket)
{
    // Allocate memory for server utils struct
    t_server_utils *utils = malloc(sizeof(*utils));
    utils->client_socket = client_socket;
    utils->ssl = ssl;
    utils->user = NULL;
    return utils;
}

static void create_client_thread(t_server_utils *utils)
{
    // Create a new thread to handle the client
    pthread_t thread;
    pthread_create(&thread, NULL, thread_handler, (void *)utils);
}

// Function to handle new client creation
void create_new_client(SSL *ssl, int client_socket)
{
    // Accept SSL connection
    accept_ssl_connection(ssl);

    // Set client socket to non-blocking mode
    set_socket_non_blocking(client_socket);

    // Initialize server utils struct
    t_server_utils *utils = initialize_server_utils(ssl, client_socket);

    // Create a new thread to handle the client
    create_client_thread(utils);
}
