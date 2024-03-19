#include "../../inc/client.h"

void mx_clear_msg_list(t_msg **list)
{
    if (list == NULL || *list == NULL)
    {
        return;
    }

    t_msg *node = *list;
    t_msg *next = NULL;

    while (node != NULL)
    {
        next = node->next;
        mx_clear_msg(&node);
        node = next;
    }

    *list = NULL;
}
