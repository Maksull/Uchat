#include "../../../inc/client.h"

// Function to clear the memory of a single message object
static void clear_single_msg(t_msg *msg)
{
    if (msg == NULL)
    {
        return;
    }

    free(msg->sender_name);
    free(msg->text);
    free(msg->date_str);
    free(msg->avatar_path);
    free(msg);
}

// Function to clears the memory of messages
void mx_clear_msg(t_msg **p)
{
    // Check if the pointer to the message object or the message object itself is NULL
    if (!p || !(*p))
    {
        return; // Return if the pointer is NULL
    }

    clear_single_msg(*p);
    *p = NULL; // Set the pointer to the message object to NULL
}
