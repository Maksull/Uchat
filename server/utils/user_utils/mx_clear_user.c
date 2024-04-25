#include "../../inc/server.h"

// Function clears the memory allocated for a user structure
void mx_clear_user(t_user **p)
{
    // Check if the pointer to the user structure is valid and if the user structure exists
    if (!p || !(*p))
    {
        return; // If not, return without performing any action
    }

    free((*p)->name);
    free((*p)->password);
    free(*p);
    *p = NULL;
}
