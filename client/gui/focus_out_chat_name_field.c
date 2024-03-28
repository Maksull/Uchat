#include "../inc/client.h"

// Function to handle focus out chat name field
void focus_out_chat_name_field(GtkWidget *widget, gpointer data)
{
    // Get the top-level window containing the widget
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget);
    (void)data;

    // Find the chat name field and the corresponding notification label within the top-level window
    GtkWidget *chat_name_field = get_widget_by_name_r(toplevel, "chat_name_field");
    GtkWidget *chat_name_notify_label = get_widget_by_name_r(toplevel, "chat_name_notify_label");
    validate_name_field(chat_name_field, chat_name_notify_label); // Validate the content of the chat name field and update the notification label
}
