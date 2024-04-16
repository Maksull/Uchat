#include "../../inc/client.h"

// Handle new message received from the server
int handle_new_msg(t_chat *curr_chat, int message_id, bool is_current)
{
    // Get the ID of the last message in the current chat
    t_msg *curr_last_node = mx_get_last_msg_node(curr_chat->messages);
    int curr_last_msg_id = curr_last_node ? curr_last_node->message_id : 0;
    // Get the ID of the last new message in the current chat
    int last_new_msg_id = curr_chat->last_new_msg ? curr_chat->last_new_msg->message_id : 0;

    // Request details of the new message from the server
    handle_get_msg_req(curr_chat->id, message_id);
    t_msg *new_msg = NULL;

    // Receive and handle the response for the new message request
    if (!(new_msg = handle_get_msg_res()))
    {
        return 1; // Return 1 indicating failure
    }

    // Process the new message based on its ID and the current chat status
    if (is_current && message_id > curr_last_msg_id)
    {
        // If the new message is in the current chat and has a higher ID than the last message,
        // add it to the chat history and update the display
        if (!curr_chat->new_messages)
        {
            // If there are no new messages, directly add the new message to the chat history
            mx_msg_push_back(&curr_chat->messages, new_msg);
            curr_chat->last_new_msg = mx_get_last_msg_node(curr_chat->messages);

            // Update the chat field display based on the message count
            if (mx_msg_list_size(curr_chat->messages) == 1)
            {
                update_chat_field(); // Update the chat field display
            }
            else
            {
                add_message(curr_chat->last_new_msg); // Add the new message to the display
            }

            // Decrease the count of new messages if there are any
            if (curr_chat->new_msg_count >= 1)
            {
                curr_chat->new_msg_count -= 1;
            }
        }
        else
        {
            // If there are new messages, mark them as read and update the last new message node
            set_msgs_as_read_for(curr_chat);
            curr_chat->last_new_msg = mx_get_last_msg_node(curr_chat->messages);
        }
    }
    else if (message_id > last_new_msg_id)
    {
        // If the new message is not in the current chat but has a higher ID than the last new message,
        // add it to the list of new messages and update the new message count
        mx_msg_push_back(&curr_chat->new_messages, new_msg);
        curr_chat->last_new_msg = mx_get_last_msg_node(curr_chat->new_messages);
        curr_chat->new_msg_count += 1;
    }

    // Update the information displayed in the chat list item
    update_chatlist_item_info(curr_chat);

    g_usleep(100000); // Introduce a delay to avoid overwhelming the system

    return 0; // Return 0 indicating success
}
