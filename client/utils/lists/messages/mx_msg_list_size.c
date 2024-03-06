#include "../../../inc/client.h"

// Get the size of a message list
int mx_msg_list_size(t_msg *list)
{
    // Check if the list is NULL
    if (list == NULL)
    {
        return 0;
    }

    // Traverse the list and count the nodes
    int size = 0;
    while (head != NULL)
    {
        head = head->next;
        ++size;
    }

    return size;
}
