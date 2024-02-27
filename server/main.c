#include "./inc/server.h"

static void initialize_server(struct sockaddr_in *server_address, const char *port)
{
    // Set up server address structure
    server_address->sin_family = AF_INET;         // Set address family to IPv4
    server_address->sin_addr.s_addr = INADDR_ANY; // Bind to any available local IP address
    server_address->sin_port = htons(atoi(port)); // Convert port number to network byte order
}

static void handle_client_connection(int client_socket, SSL_CTX *ctx)
{
    // Initialize SSL connection
    SSL *ssl = SSL_new(ctx);
    SSL_set_fd(ssl, client_socket); // Associate SSL structure with the client socket

    // Create a new client thread
    create_new_client(ssl, client_socket);
}

static void accept_and_handle_clients(int server_socket, SSL_CTX *ctx)
{
    socklen_t address_size = sizeof(struct sockaddr_in);

    // Accept incoming connections and handle them indefinitely
    while (1)
    {
        // Accept incoming client connections
        struct sockaddr_in client_address;
        int client_socket;
        if ((client_socket = accept(server_socket, (struct sockaddr *)&client_address, &address_size)) != -1)
        {
            // Handle client connection
            handle_client_connection(client_socket, ctx);
        }
        else
        {
            // Handle errors if accepting client connection fails
            handle_error(strerror(errno));
        }
    }
}


static void cleanup(SSL_CTX *ctx, int server_socket)
{
    // Clean up SSL context
    SSL_CTX_free(ctx);

    // Close server socket
    close(server_socket);
}

int main(int argc, char *argv[])
{
    (void)argc; // Suppress unused parameter warning
    handle_cli_arg_errors(argv);

    init_daemon();

    // Initialize SSL context
    SSL_CTX *ctx = NULL;
    init_ssl(&ctx);

    // Set up server address structure and initialize server socket
    struct sockaddr_in server_address;
    initialize_server(&server_address, argv[1]);

    // Accept incoming connections and handle them indefinitely
    int server_socket = init_server_socket((struct sockaddr *)&server_address, sizeof(server_address));
    accept_and_handle_clients(server_socket, ctx);

    // Clean up resources
    cleanup(ctx, server_socket);

    return EXIT_FAILURE;
}
