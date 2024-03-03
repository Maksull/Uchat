#include "../../inc/client.h"

// Establish a connection with the server via the port
void connect_to_server(const char *ip_address, int port, int *server_fd, SSL_CTX **ctx, SSL **ssl)
{
    struct sockaddr_in server_addr; // Structure to hold server address information

    init_ssl(ctx); // Initialize SSL context

    server_addr.sin_family = AF_INET; // Set address family to IPv4
    server_addr.sin_addr.s_addr = inet_addr(ip_address); // Set server IP address
    server_addr.sin_port = htons(port); // Set server port

    // Create socket
    if ((*server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        handle_error(strerror(errno)); // Handle socket creation error
        exit(EXIT_FAILURE); // Exit with failure status
    }

    // Connect to server
    if (connect(*server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        handle_error(strerror(errno)); // Handle connection error
        exit(EXIT_FAILURE); // Exit with failure status
    }

    connect_ssl(ssl, server_fd, ctx); // Establish SSL connection with the server
}
