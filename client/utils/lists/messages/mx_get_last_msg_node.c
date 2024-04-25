#include "../../../inc/client.h"

// Get the last node of a message list
t_msg *mx_get_last_msg_node(t_msg *list)
{
    // Check if the list is NULL
    if (!list)
    {
        return NULL;
    }
    // Traverse the list until the last node
    while (list->next)
    {
        list = list->next;
    }
    
    return list;
}
