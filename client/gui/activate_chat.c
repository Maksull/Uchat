#include "../inc/client.h"

// Function to activate chat
void activate_chat(GtkWidget *chatlist_item)
{
    set_current_chat(chatlist_item);         // Set the selected chat list item as the current chat
    set_chatlist_item_active(chatlist_item); // Mark the selected chat list item as active
    build_rightbar_chat();                   // Update the right sidebar to display information related to the selected chat
}
