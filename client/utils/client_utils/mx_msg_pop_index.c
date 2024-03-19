#include "../../inc/client.h"

void mx_msg_pop_index(t_msg **list, int index)
{
    int size = 0;
    t_msg *head = *list;
    while (head != NULL)
    {
        head = head->next;
        ++size;
    }

    if (index <= 0)
    {
        mx_msg_pop_front(list);
        return;
    }
    else if (index >= size)
    {
        mx_msg_pop_back(list);
        return;
    }

    t_msg *current = *list;
    for (int i = 0; current != NULL && i < (index - 1); ++i)
    {
        current = current->next;
    }
    t_msg *next = current->next->next;
    mx_clear_msg(&current->next);
    current->next = next;
}
