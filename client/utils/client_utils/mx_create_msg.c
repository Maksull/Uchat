#include "../../inc/client.h"

t_msg *mx_create_msg(int msg_id, int user_id, const char *user_name, int chat_id, const char *text, const char *date_str, t_avatar_color color)
{
    t_msg *new_node = malloc(sizeof(t_msg));

    new_node->message_id = msg_id;
    new_node->chat_id = chat_id;
    new_node->sender_id = user_id;
    new_node->sender_name = mx_strdup(user_name);
    new_node->text = mx_strdup(text);
    new_node->date_str = mx_strdup(date_str);
    new_node->avatar_color = color;
    new_node->avatar_path = NULL;
    new_node->next = NULL;

    return new_node;
}
