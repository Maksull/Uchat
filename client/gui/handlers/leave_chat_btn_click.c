#include "../../inc/client.h"

// Function to handle leave chat button click
void leave_chat_btn_click(GtkWidget *widget, gpointer data)
{
    (void)data;
    int response_code = handle_leave_chat_req(utils->current_chat->name); // Send a request to leave the current chat

    // If leaving the chat was successful
    if (response_code == R_SUCCESS)
    {
        utils->current_chat = NULL; // Clear the current chat
        update_chatlist();          // Update the chat list

        // Close the chat window
        GtkWidget *toplevel = gtk_widget_get_toplevel(widget);
        gtk_widget_destroy(toplevel);
    }
}
