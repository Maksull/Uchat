#include "../../../inc/client.h"

// Function to get chat by its ID
t_chat *mx_get_chat_by_id(t_chat *list, int chat_id)
{
    // Traverse the linked list of chat objects
    while (list)
    {
        // Check if the current chat object's ID matches the specified chat ID
        if (list->id == chat_id)
            return list; // Return a pointer to the chat object if found

        list = list->next; // Move to the next chat object in the list
    }

    return NULL; // Return NULL if the chat object with the specified ID is not found
}
