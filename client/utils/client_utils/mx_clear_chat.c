#include "../../inc/client.h"

void mx_clear_chat(t_chat **p)
{

    if (!p || !(*p))
    {
        return;
    }

    if ((*p)->name)
    {
        free((*p)->name);
    }

    free(*p);
    *p = NULL;
}
