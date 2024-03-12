#include "../../inc/client.h"

// Function to modify the global user information
void modify_global_user(const char *new_name, const char *new_pass)
{
    t_user *curr_user = utils->current_user;

    // If new_name is provided, update the user's name
    if (new_name)
    {
        mx_strdel(&curr_user->name);           // Free the previous name
        curr_user->name = mx_strdup(new_name); // Set the new name
    }

    // If new_pass is provided, update the user's password
    if (new_pass)
    {
        mx_strdel(&curr_user->password);           // Free the previous password
        curr_user->password = mx_strdup(new_pass); // Set the new password
    }
}
