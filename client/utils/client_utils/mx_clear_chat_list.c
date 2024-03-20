#include "../../inc/client.h"

// Function to clear the memory associated with a linked list of chat objects
void mx_clear_chat_list(t_chat **list)
{
    // Check if the pointer to the list or the list itself is NULL
    if (list == NULL || *list == NULL)
    {
        return; // Return if the list is empty
    }

    // Initialize variables
    t_chat *node = *list; // Pointer to traverse the list
    t_chat *next = NULL; // Pointer to store the next node in the list

    // Traverse the list and clear memory associated with each chat object
    while (node != NULL)
    {
        next = node->next; // Store the next node before clearing the current one
        mx_clear_msg_list(&node->messages); // Clear the messages associated with the chat
        mx_clear_msg_list(&node->new_messages); // Clear the new messages associated with the chat
        mx_clear_chat(&node); // Clear the chat object itself
        node = next; // Move to the next node in the list
    }

    *list = NULL; // Set the pointer to the head of the list to NULL
}
