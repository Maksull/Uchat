#include "../inc/server.h"

// Function performs cleanup operations for a client connection
void client_cleanup(t_server_utils *utils, bool is_client_exit)
{
    // Clear user data associated with the client
    mx_clear_user(&utils->user);

    // If the client is exiting, perform additional cleanup steps
    if (is_client_exit)
    {
        // Free SSL resources
        SSL_free(utils->ssl);
        // Close the client socket
        close(utils->client_socket);
        // Deallocate memory for the server utilities structure
        free(utils);
    }

    logger("Cleanup completed\n", INFO_LOG);
}
