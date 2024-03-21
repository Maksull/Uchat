#include "../../inc/client.h"

// Function to get message by its ID
t_msg *mx_get_msg_by_id(t_msg *list, int id)
{
    // Traverse the linked list of message objects
    while (list)
    {
        // Check if the current message object's ID matches the specified message ID
        if (list->message_id == id)
        {
            return list; // Return a pointer to the message object if found
        }

        list = list->next; // Move to the next message object in the list
    }

    return NULL; // Return NULL if the message object with the specified ID is not found
}
