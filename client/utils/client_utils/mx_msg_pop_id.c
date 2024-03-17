#include "../../inc/client.h"

void mx_msg_pop_id(t_msg **list, int msg_id)
{
    t_msg *temp = *list;
    for (int i = 0; temp; temp = temp->next, ++i)
    {
        if (temp->message_id == msg_id)
        {
            mx_msg_pop_index(list, i);
            return;
        }
    }
}
