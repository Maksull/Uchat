#include "../../inc/client.h"

// Function to add a message to the global message list
t_response_code add_to_global_msglist(t_msg *new_msg)
{
    // Find the chat corresponding to the new message's chat ID
    t_chat *curr_chat = mx_get_chat_by_id(utils->chatlist, new_msg->chat_id);
    if (!curr_chat)
    {
        return R_CHAT_NOENT;
    }

    // Add the new message to the chat's message list
    mx_msg_push_back(&curr_chat->messages, new_msg);

    // Update the last new message of the chat and its information in the chat list
    curr_chat->last_new_msg = mx_get_last_msg_node(curr_chat->messages);
    update_chatlist_item_info(curr_chat);

    return R_SUCCESS;
}
