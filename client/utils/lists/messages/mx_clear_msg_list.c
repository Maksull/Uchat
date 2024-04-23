#include "../../../inc/client.h"

// Function to clear the memory of messages list
void mx_clear_msg_list(t_msg **list)
{
    // Check if the pointer to the list or the list itself is NULL
    if (list == NULL || *list == NULL)
    {
        return; // Return if the list is empty
    }

    // Initialize variables
    t_msg *node = *list; // Pointer to traverse the list
    t_msg *next = NULL; // Pointer to store the next node in the list

    // Traverse the list and clear memory associated with each message object
    while (node)
    {
        next = node->next; // Store the next node before clearing the current one
        mx_clear_msg(&node); // Clear the message object itself
        node = next; // Move to the next node in the list
    }

    *list = NULL; // Set the pointer to the head of the list to NULL
}
