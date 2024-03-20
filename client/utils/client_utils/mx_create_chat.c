#include "../../inc/client.h"

// Function to create chat
t_chat *mx_create_chat(int id, const char *name, int permissions, int chat_color)
{
    t_chat *new_node = malloc(sizeof(t_chat)); // Allocate memory for the new chat object

    // Assign values to the fields of the new chat object
    new_node->id = id;
    new_node->name = name ? mx_strdup(name) : NULL; // Duplicate the name string if not NULL
    new_node->permissions = permissions;
    new_node->avatar_color = chat_color;
    new_node->new_msg_count = 0;
    new_node->messages = NULL;
    new_node->new_messages = NULL;
    new_node->last_new_msg = NULL;
    new_node->next = NULL;

    return new_node; // Return a pointer to the newly created chat object
}
