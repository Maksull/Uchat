#include "../../../inc/client.h"

// Function to initialize a chat node
static void initialize_chat_node(t_chat *new_node, int id, const char *name, int permissions, int chat_color)
{
    // Assign values to the fields of the chat node
    new_node->id = id;
    new_node->name = name ? mx_strdup(name) : NULL; // Duplicate the name string if not NULL
    new_node->permissions = permissions;
    new_node->avatar_color = chat_color;
    new_node->new_msg_count = 0;
    new_node->messages = NULL;
    new_node->new_messages = NULL;
    new_node->last_new_msg = NULL;
    new_node->next = NULL;
}

// Function to create chat
t_chat *mx_create_chat(int id, const char *name, int permissions, int chat_color)
{
    t_chat *new_node = malloc(sizeof(t_chat)); // Allocate memory for the new chat object

    if (new_node == NULL)
    {
        exit(EXIT_FAILURE);
    }

    // Initialize the chat node
    initialize_chat_node(new_node, id, name, permissions, chat_color);

    return new_node; // Return a pointer to the newly created chat object
}
