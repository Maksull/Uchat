#include "../../inc/client.h"

void mx_msg_pop_back(t_msg **head)
{

    if (head == NULL || *head == NULL)
    {
        return;
    }

    if ((*head)->next == NULL)
    {
        mx_clear_msg(head);
        return;
    }

    t_msg *prelast = *head;
    while (prelast->next->next != NULL)
    {

        prelast = prelast->next;
    }
    mx_clear_msg(&prelast->next);
    prelast->next = NULL;
}
