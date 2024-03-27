#include "../../../inc/client.h"

// Function to clears the memory of messages
void mx_clear_msg(t_msg **p)
{
    // Check if the pointer to the message object or the message object itself is NULL
    if (!p || !(*p))
    {
        return; // Return if the pointer is NULL
    }

    // Free the memory allocated for the sender's name, message text, date string, and avatar path
    free((*p)->sender_name);
    free((*p)->text);
    free((*p)->date_str);
    free((*p)->avatar_path);
    free(*p); // Free the memory allocated for the message object
    *p = NULL; // Set the pointer to the message object to NULL
}
