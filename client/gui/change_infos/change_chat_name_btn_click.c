#include "../../inc/client.h"

// Function to handle change chat name
void change_chat_name_btn_click(GtkWidget *widget, gpointer data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget); // Get the top-level window containing the widget
    (void)data;

    // Find the chat name field and the corresponding notification label within the top-level window
    GtkWidget *chat_name_field = get_widget_by_name_r(toplevel, "chat_name_field");
    GtkWidget *chat_name_notify_label = get_widget_by_name_r(toplevel, "chat_name_notify_label");

    // Validate the new chat name; if it's invalid, return
    if (!validate_name_field(chat_name_field, chat_name_notify_label))
    {
        return;
    }

    char *new_chat_name = (char *)gtk_entry_get_text(GTK_ENTRY(chat_name_field)); // Get the new chat name entered by the user

    int response_code = handle_edit_chat_req(utils->current_chat->id, new_chat_name);   // Send a request to edit the chat name and get the response code
    handle_edit_chat_response_code(response_code, chat_name_field, chat_name_notify_label); // Handle the response code and update the UI accordingly
}
