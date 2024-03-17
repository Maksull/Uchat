#include "../../inc/client.h"

// Function to perform cleanup operations for a user
void user_cleanup(t_user **user)
{
    // Checking if the user pointer is valid and pointing to a valid user structure
    if (!user || !(*user))
    {
        // If user pointer is invalid or points to NULL, return without performing cleanup
        return;
    }
    
    // Freeing memory allocated for user details
    mx_strdel(&(*user)->name);
    mx_strdel(&(*user)->password);
    mx_strdel(&(*user)->avatar_path);
    
    // Freeing memory allocated for the user structure itself
    free(*user);
    
    // Setting the user pointer to NULL after cleanup
    *user = NULL;
}
