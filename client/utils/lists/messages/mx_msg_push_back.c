#include "../../../inc/client.h"

// Append a message node to the end of a message list
void mx_msg_push_back(t_msg **list, t_msg *new_node)
{
    // Check if the list is NULL
    if (list != NULL && *list == NULL)
    {
        *list = new_node;
        return;
    }

    // Traverse the list to find the last node
    t_msg *last = *list;
    while (last->next)
    {
        last = last->next;
    }
    
    // Append the new node to the end of the list
    new_node->next = last->next;
    last->next = new_node;
}
