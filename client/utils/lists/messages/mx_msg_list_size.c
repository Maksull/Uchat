#include "../../../inc/client.h"

int mx_msg_list_size(t_msg *list)
{
    if (list == NULL)
    {
        return 0;
    }

    t_msg *head = list;
    int size = 0;

    while (head != NULL)
    {

        head = head->next;
        ++size;
    }

    return size;
}
