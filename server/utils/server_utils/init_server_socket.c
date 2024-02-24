#include "../../inc/server.h"

// Function to initialize the server socket
int init_server_socket(struct sockaddr *server_address, socklen_t address_size)
{
    int server_socket = 0;

    // Create a TCP socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0); // Create a TCP socket
    if (server_socket == -1)
    {
        handle_error(strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Bind the socket to the server address
    if (bind(server_socket, serv_address, address_size) == -1)
    {
        handle_error(strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Start listening on the socket for incoming connections
    if (listen(server_socket, 10) == -1)
    {
        handle_error(strerror(errno));
    }

    return server_socket;
}
