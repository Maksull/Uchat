#include "../../inc/client.h"

// Function to calculate the size of a linked list of chat objects
int mx_chat_list_size(t_chat *list)
{
    // Check if the list pointer is NULL
    if (list == NULL)
    {
        return 0; // Return 0 if the list is empty
    }

    // Initialize variables
    t_chat *head = list; // Pointer to traverse the list
    int size = 0; // Variable to store the size of the list

    // Traverse the list and count the number of chat objects
    while (head != NULL)
    {
        head = head->next; // Move to the next chat object
        ++size; // Increment the size counter
    }

    return size; // Return the total size of the list
}
