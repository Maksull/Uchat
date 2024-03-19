#include "../../inc/client.h"

void mx_chat_push_back(t_chat **list, int chat_id, const char *name, int permissions, int chat_color)
{
    t_chat *new_node = mx_create_chat(chat_id, name, permissions, chat_color);
    if (list != NULL && *list == NULL)
    {
        *list = new_node;
        return;
    }

    t_chat *last = *list;
    while (last->next != NULL)
    {
        last = last->next;
    }

    new_node->next = last->next;
    last->next = new_node;
}
