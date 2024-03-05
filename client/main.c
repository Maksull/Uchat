#include "../inc/client.h"

t_client_utils *utils;
GtkWidget *main_window;

// Main function
int main(int argc, char **argv)
{
    (void)argc; // Suppress unused parameter warning
    handle_arg_errors(argv); // Check command line arguments
    srand(time(NULL)); // Seed the random number generator

    int server_socket = 0; // Variable to store server socket file descriptor
    SSL_CTX *ctx = NULL; // SSL context
    SSL *ssl = NULL; // SSL structure

    // Connect to the server
    connect_to_server(argv[1], atoi(argv[2]), &server_socket, &ctx, &ssl);
    // Initialize the client
    client_init(server_socket, ssl, ctx);

    gtk_init(&argc, &argv); // Initialize GTK

    load_css(); // Load CSS styles
    build_authorization_window(); // Build the authorization window

    // Create a new thread for handling server updates
    pthread_create(&utils->th_reader, NULL, handle_server_updates, utils);

    gtk_main(); // Run the GTK main loop

    return EXIT_SUCCESS; // Return success status
}
