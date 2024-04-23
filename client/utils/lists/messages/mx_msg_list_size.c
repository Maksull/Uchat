#include "../../../inc/client.h"

// Computes the size of a linked list of t_msg nodes.
int mx_msg_list_size(t_msg *list)
{
    // If the list is empty (NULL), its size is 0.
    if (list == NULL)
    {
        return 0;
    }

    // Initialize a pointer 'head' to the beginning of the list.
    t_msg *head = list;

    // Initialize a variable 'size' to keep track of the size of the list.
    int size = 0;

    // Traverse the list until the end is reached (head becomes NULL).
    while (head)
    {
        // Move 'head' to the next node in the list.
        head = head->next;

        // Increment the size counter for each node traversed.
        ++size;
    }

    // Return the computed size of the linked list.
    return size;
}
