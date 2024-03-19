#include "../../inc/client.h"

void mx_msg_pop_front(t_msg **head)
{

    if (head == NULL || *head == NULL)
    {
        return;
    }

    if ((*head)->next == NULL)
    {
        mx_clear_msg(head);
        *head = NULL;
        return;
    }

    t_msg *temp = *head;
    *head = (*head)->next;
    mx_clear_msg(&temp);
}
