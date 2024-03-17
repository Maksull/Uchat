#include "../../inc/client.h"

t_msg *mx_get_msg_by_id(t_msg *list, int id)
{
    while (list)
    {
        if (list->message_id == id)
        {
            return list;
        }
            

        list = list->next;
    }
    return NULL;
}
