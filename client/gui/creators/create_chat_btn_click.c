#include "../../inc/client.h"

// Function to handle button click to create a chat
void create_chat_btn_click(GtkWidget *widget, gpointer data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget); // Get the top-level window containing the widget
    (void)data;
    // Get the chat name field and notification label from the top-level window
    GtkWidget *chat_name_field = get_widget_by_name_r(toplevel, "chat_name_field");
    GtkWidget *chat_name_notify_label = get_widget_by_name_r(toplevel, "chat_name_notify_label");

    // Validate the chat name field
    if (!validate_name_field(chat_name_field, chat_name_notify_label))
    {
        return;
    }

    char *group_name = (char *)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(chat_name_field))); // Retrieve the group name from the chat name field

    int response_code = handle_create_chat_req(group_name);                               // Send a request to create a chat with the specified name
    handle_create_chat_response_code(response_code, chat_name_field, chat_name_notify_label); // Handle the response code from the server
}
