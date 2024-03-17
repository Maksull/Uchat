#include "../../inc/client.h"

int mx_chat_list_size(t_chat *list)
{

    if (list == NULL)
    {
        return 0;
    }

    t_chat *head = list;
    int size = 0;
    while (head != NULL)
    {

        head = head->next;
        ++size;
    }

    return size;
}
