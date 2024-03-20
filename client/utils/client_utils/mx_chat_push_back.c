#include "../../inc/client.h"

// Function to add a new chat object
void mx_chat_push_back(t_chat **list, int chat_id, const char *name, int permissions, int chat_color)
{
    t_chat *new_node = mx_create_chat(chat_id, name, permissions, chat_color); // Create a new chat node
    // If the list is empty, make the new node the head of the list
    if (list != NULL && *list == NULL)
    {
        *list = new_node;
        return;
    }

    t_chat *last = *list; // Traverse the list to find the last node
    while (last->next != NULL)
    {
        last = last->next;
    }

    // Append the new node to the end of the list
    new_node->next = last->next;
    last->next = new_node;
}
