#include "../inc/client.h"

// Function to handle join chat event
void join_chat_event(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
    char *chat_name = (char *)gtk_widget_get_name(widget); // Extract the chat name from the widget's name

    // Handle single-click event (set chat item as active)
    if (event->type == GDK_BUTTON_PRESS && event->button == 1)
    {
        set_chatlist_item_active(widget);
    }
    else if (event->type == GDK_DOUBLE_BUTTON_PRESS && event->button == 1) // Handle double-click event (attempt to join chat)
    {
        // Request to join the chat and handle the response
        int response_code = handle_join_chat_request(chat_name);
        handle_join_chat_response_code(response_code, chat_name);
    }
    (void)data;
}
