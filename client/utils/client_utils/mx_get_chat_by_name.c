#include "../../inc/client.h"

t_chat *mx_get_chat_by_name(t_chat *list, const char *name)
{
    while (list)
    {

        if (mx_strcmp(list->name, name) == 0)
            return list;

        list = list->next;
    }

    return NULL;
}
