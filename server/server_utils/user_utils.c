#include "../inc/server.h"

// Function clears the memory allocated for a user structure
void mx_clear_user(t_user** p) {

    if (!p || !(*p))
        return;

    free((*p)->name);
    free((*p)->password);
    free(*p);
    *p = NULL;

}