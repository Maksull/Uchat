#include "../../../inc/client.h"

// Function to remove last message object from a linked list
void mx_msg_pop_back(t_msg **head)
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
        return;
    }

    // Traverse the list to find the second-to-last message
    t_msg *prelast = *head;
    while (prelast->next->next != NULL)
    {

        prelast = prelast->next;
    }

    // Clear the last message and update the next pointer of the second-to-last message to NULL
    mx_clear_msg(&prelast->next);
    prelast->next = NULL;
}
