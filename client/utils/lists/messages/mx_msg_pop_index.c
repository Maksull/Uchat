#include "../../../inc/client.h"

// Function to remove a message object at the specified index from a linked list of message objects
void mx_msg_pop_index(t_msg **list, int index)
{
    int size = 0; // Variable to store the size of the list
    t_msg *head = *list; // Pointer to traverse the list to calculate its size

    // Traverse the list to calculate its size
    while (head != NULL)
    {
        head = head->next;
        ++size;
    }

    // If the index is less than or equal to 0, remove the first message from the list
    if (index <= 0)
    {
        mx_msg_pop_front(list);
        return;
    }
    else if (index >= size) // If the index is greater than or equal to the size of the list, remove the last message from the list
    {
        mx_msg_pop_back(list);
        return;
    }

    t_msg *current = *list; // Traverse the list to find the message at the specified index
    for (int i = 0; current != NULL && i < (index - 1); ++i)
    {
        current = current->next;
    }
    // Remove the message at the specified index by updating pointers and freeing memory
    t_msg *next = current->next->next;
    mx_clear_msg(&current->next);
    current->next = next;
}
