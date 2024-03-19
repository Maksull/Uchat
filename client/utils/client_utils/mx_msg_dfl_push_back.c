#include "../../inc/client.h"

void mx_msg_dfl_push_back(t_msg **list, int msg_id, int user_id, const char *user_name, int chat_id,
                          const char *text, const char *date_str, t_avatar_color color)
{

    t_msg *new_node = mx_create_msg(msg_id, user_id, user_name, chat_id, text, date_str, color);
    mx_msg_push_back(list, new_node);
}
