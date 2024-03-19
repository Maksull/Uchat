#include "../../inc/client.h"

t_chat *mx_create_chat(int id, const char *name, int permissions, int chat_color)
{
    t_chat *new_node = malloc(sizeof(t_chat));

    new_node->id = id;
    new_node->name = name ? mx_strdup(name) : NULL;
    new_node->permissions = permissions;
    new_node->avatar_color = chat_color;
    new_node->new_msg_count = 0;
    new_node->messages = NULL;
    new_node->new_messages = NULL;
    new_node->last_new_msg = NULL;
    new_node->next = NULL;
    return new_node;
}
