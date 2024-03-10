#include "../inc/client.h"

// Function to handle chatlist item on click
void chatlist_item_on_click(GtkWidget *chatlist_item, gpointer data)
{
    activate_chat(chatlist_item); // activate chat
    (void)data;
}
