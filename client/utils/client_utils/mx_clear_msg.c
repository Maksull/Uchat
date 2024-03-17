#include "../../inc/client.h"

void mx_clear_msg(t_msg **p)
{
    if (!p || !(*p))
    {
        return;
    }

    free((*p)->sender_name);
    free((*p)->text);
    free((*p)->date_str);
    free((*p)->avatar_path);
    free(*p);
    *p = NULL;
}
