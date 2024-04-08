#include "../inc/client.h"

// Thread handler for checking and handling server updates
void *handle_server_updates(void *arg)
{
    (void)arg; // Suppress unused parameter warning
    while (1)
    {
        if (!utils) // Check if utils is NULL
            break; // Exit loop if utils is NULL

        if (utils && utils->is_suspended) // Check if utils is not NULL and if updates are suspended
            continue; // Skip iteration if updates are suspended

        t_chat *curr_chat = utils ? utils->chatlist : NULL; // Get the list of chats from utils
        while (curr_chat) // Iterate over each chat in the list
        {
            bool is_current = utils->current_chat && curr_chat->id == utils->current_chat->id; // Check if the current chat is the active chat
            int last_msg_id = handle_last_msg_id_req(curr_chat->id); // Get the ID of the last message in the current chat
            if (last_msg_id <= 0) // Check if the last message ID is invalid
            {
                curr_chat = curr_chat ? curr_chat->next : NULL; // Move to the next chat
                continue; // Continue to the next iteration
            }

            int curr_last_msg_id = curr_chat->last_new_msg ? curr_chat->last_new_msg->message_id : 0; // Get the ID of the last new message in the current chat
            if (last_msg_id <= curr_last_msg_id && !is_current) // Check if there are no new messages in the current chat and it's not the active chat
            {
                curr_chat = curr_chat ? curr_chat->next : NULL; // Move to the next chat
                continue; // Continue to the next iteration
            }

            handle_new_msg(curr_chat, last_msg_id, is_current); // Handle new messages in the current chat

            curr_chat = curr_chat ? curr_chat->next : NULL; // Move to the next chat
            g_usleep(500000); // Sleep for 0.5 seconds
        }
        g_usleep(500000); // Sleep for 0.5 seconds
    }
    return NULL; // Return NULL when the function completes
}
