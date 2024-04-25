#include "../../../inc/client.h"

// Function to handle clear chat
void mx_clear_chat(t_chat **p)
{
    // Check if the pointer to the chat object or the chat object itself is NULL
    if (!p || !(*p))
    {
        return; // Return if the pointer is NULL
    }

    // Free the memory allocated for the name of the chat object
    if ((*p)->name)
    {
        free((*p)->name);
    }

    free(*p); // Free the memory allocated for the chat object
    *p = NULL; // Set the pointer to the chat object to NULL
}
