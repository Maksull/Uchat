#include "../../inc/client.h"

// Function to perform cleanup operations for the client
void client_cleanup(bool is_client_exit)
{
    // Locking the mutex to ensure thread safety during cleanup
    pthread_mutex_lock(&utils->lock);
    
    // Cleaning up current user details and chat list
    user_cleanup(&utils->current_user);
    mx_clear_chat_list(&utils->chatlist);
    
    // Unlocking the mutex after cleanup
    pthread_mutex_unlock(&utils->lock);

    // Additional cleanup steps if the client is exiting
    if (is_client_exit)
    {
        // Destroying the mutex
        pthread_mutex_destroy(&utils->lock);
        
        // Freeing SSL resources
        SSL_free(utils->ssl);
        SSL_CTX_free(utils->ctx);
        
        // Freeing memory allocated for the utility structure and setting pointer to NULL
        free(utils);
        utils = NULL;
    }
}
