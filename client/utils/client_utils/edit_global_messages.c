#include "../../inc/client.h"

// Function to edit global messages
void edit_global_messages(int message_id, const char *new_msg_text)
{
    // Find the message to edit by its ID in the current chat's message list
    t_msg *msg_to_edit = mx_get_msg_by_id(utils->current_chat->messages, message_id);
    if (msg_to_edit)
    {
        // Free the current text of the message and allocate memory for the new text
        mx_strdel(&msg_to_edit->text);
        msg_to_edit->text = mx_strdup(new_msg_text);

        // Update the chat list item information
        update_chatlist_item_info(utils->current_chat);
    }
}
