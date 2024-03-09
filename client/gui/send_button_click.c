#include "../inc/client.h"

// Function to handle send button click
void send_button_click(GtkWidget *widget, gpointer new_message_field)
{
    if (widget) { };

    // Get the chat container and messaging label widgets
    GtkWidget *chat_container = get_widget_by_name_r(main_window, "chat");
    GtkWidget *messaging_label = get_widget_by_name_r(chat_container, "messaging_label");

    // Retrieve the new message from the new message field
    gchar new_message[2048];
    sprintf(new_message, "%s", gtk_entry_get_text(new_message_field));
    // Check if the new message is empty
    if (!new_message[0])
    {
        return;
    }

    // Remove the "No messages here yet..." label if present
    if (messaging_label)
    {
        gtk_widget_destroy(messaging_label);
        messaging_label = gtk_label_new("No messages here yet...");
    }

    gtk_entry_set_text(new_message_field, ""); // Clear the new message field

    // Send the message to the server and add it to the chat interface if successful
    if (handle_send_msg_request(new_message) == R_SUCCESS)
    {
        add_message(mx_get_last_msg_node(utils->current_chat->messages));
    }
}
