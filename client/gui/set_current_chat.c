#include "../inc/client.h"

// Function to set current chat
void set_current_chat(GtkWidget *chatlist_item)
{
    int chat_id = get_chatlist_item_id(chatlist_item); // Retrieve the chat ID associated with the selected chat list item
    utils->current_chat = mx_get_chat_by_id(utils->chatlist, chat_id); // Find the corresponding chat in the chat list by its ID
}
