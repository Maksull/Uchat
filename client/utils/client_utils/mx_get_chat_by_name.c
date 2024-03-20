#include "../../inc/client.h"

// Function to get chat by its name
t_chat *mx_get_chat_by_name(t_chat *list, const char *name)
{
    // Traverse the linked list of chat objects
    while (list)
    {
        // Check if the current chat object's name matches the specified chat name
        if (mx_strcmp(list->name, name) == 0)
            return list; // Return a pointer to the chat object if found

        list = list->next; // Move to the next chat object in the list
    }

    return NULL; // Return NULL if the chat object with the specified name is not found
}
