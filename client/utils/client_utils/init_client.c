#include "../../inc/client.h"

static void initialize_utils_struct(int server_fd, SSL *ssl, SSL_CTX *ctx, t_utils *utils)
{
    int flags = fcntl(server_fd, F_GETFL, 0);      // Get file status flags
    fcntl(server_fd, F_SETFL, flags | O_NONBLOCK); // Set socket to non-blocking mode
    fcntl(server_fd, F_SETFD, O_NONBLOCK);         // Set socket file descriptor to non-blocking

    pthread_mutex_init(&utils->lock, NULL); // Initialize mutex for thread safety
    pthread_mutex_lock(&utils->lock);       // Lock mutex
    utils->server_fd = server_fd;           // Set server file descriptor
    utils->ssl = ssl;                       // Set SSL object
    utils->ctx = ctx;                       // Set SSL context
    utils->current_user = NULL;             // Initialize current user to NULL
    utils->current_chat = NULL;             // Initialize current chat to NULL
    utils->chatlist = NULL;                 // Initialize chat list to NULL
    utils->is_suspended = true;             // Set update handling to suspended by default
    pthread_mutex_unlock(&utils->lock);     // Unlock mutex
}

// Initialize the client
void client_init(int server_fd, SSL *ssl, SSL_CTX *ctx)
{
    utils = malloc(sizeof(*utils)); // Allocate memory for utils structure

    if (utils == NULL)
    {
        exit(EXIT_FAILURE);
    }

    // Initialize utils structure
    initialize_utils_struct(server_fd, ssl, ctx, utils);
}
