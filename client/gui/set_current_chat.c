#include "../inc/client.h"

// Function to get chatlist item id
static int get_chatlist_item_id(GtkWidget *chatlist_item)
{
    int id;
    GtkWidget *id_label = get_widget_by_name_r(chatlist_item, "chat_id"); // Get the widget representing the label containing the chat ID
    id = mx_atoi((char *)gtk_label_get_text(GTK_LABEL(id_label)));        // Extract the text content of the label and convert it to an integer ID

    return id;
}

// Function to set current chat
void set_current_chat(GtkWidget *chatlist_item)
{
    int chat_id = get_chatlist_item_id(chatlist_item);                 // Retrieve the chat ID associated with the selected chat list item
    utils->current_chat = mx_get_chat_by_id(utils->chatlist, chat_id); // Find the corresponding chat in the chat list by its ID
}
