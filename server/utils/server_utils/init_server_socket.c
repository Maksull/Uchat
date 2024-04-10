#include "../../inc/server.h"

// Function to create a TCP socket
static int create_tcp_socket()
{
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        handle_error(strerror(errno));
        exit(EXIT_FAILURE);
    }
    return server_socket;
}

// Function to bind the socket to the server address
static void bind_socket(int server_socket, struct sockaddr *server_address, socklen_t address_size)
{
    if (bind(server_socket, server_address, address_size) == -1)
    {
        handle_error(strerror(errno));
        exit(EXIT_FAILURE);
    }
}

// Function to start listening on the socket for incoming connections
static void start_listening(int server_socket)
{
    if (listen(server_socket, 10) == -1)
    {
        handle_error(strerror(errno));
    }
}

// Function to initialize the server socket
int init_server_socket(struct sockaddr *server_address, socklen_t address_size)
{
    int server_socket = create_tcp_socket();
    bind_socket(server_socket, server_address, address_size);
    start_listening(server_socket);
    return server_socket;
}
