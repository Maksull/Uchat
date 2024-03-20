#include "../../inc/client.h"

// Function to remove first message object from a linked list
void mx_msg_pop_front(t_msg **head)
{
    // Check if the pointer to the list or the list itself is NULL
    if (head == NULL || *head == NULL)
    {
        return; // Return if the list is empty
    }

    // If there is only one message in the list, clear the message and set the head to NULL
    if ((*head)->next == NULL)
    {
        mx_clear_msg(head);
        *head = NULL;
        return;
    }

    t_msg *temp = *head; // Store the current head of the list in a temporary variable
    *head = (*head)->next; // Update the head pointer to point to the next message in the list
    mx_clear_msg(&temp); // Clear the original head message to free memory
}
