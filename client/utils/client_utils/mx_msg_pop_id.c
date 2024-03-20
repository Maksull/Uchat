#include "../../inc/client.h"

// Function to removes a message object
void mx_msg_pop_id(t_msg **list, int msg_id)
{
    t_msg *temp = *list; // Initialize a temporary pointer to traverse the list
    for (int i = 0; temp; temp = temp->next, ++i) // Loop through the list
    {
        // Check if the current message object's ID matches the specified message ID
        if (temp->message_id == msg_id)
        {
            mx_msg_pop_index(list, i); // Remove the message object at the current index
            return; // Exit the function after removing the message
        }
    }
}
