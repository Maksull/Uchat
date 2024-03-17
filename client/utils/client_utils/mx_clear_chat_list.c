#include "../../inc/client.h"

void mx_clear_chat_list(t_chat **list)
{
    if (list == NULL || *list == NULL)
    {
        return;
    }
        
    t_chat *node = *list;
    t_chat *next = NULL;

    while (node != NULL)
    {
        next = node->next;
        mx_clear_msg_list(&node->messages);
        mx_clear_msg_list(&node->new_messages);
        mx_clear_chat(&node);
        node = next;
    }

    *list = NULL;
}
