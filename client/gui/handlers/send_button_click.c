#include "../../inc/client.h"

// Function to find necessary widgets for sending messages
static void find_send_message_widgets(GtkWidget **chat_container, GtkWidget **messaging_label)
{
    *chat_container = get_widget_by_name_r(main_window, "chat");
    *messaging_label = get_widget_by_name_r(*chat_container, "messaging_label");
}

// Function to check if the new message is empty
static bool is_new_message_empty(gchar *new_message)
{
    return !new_message[0];
}

// Function to remove the "No messages here yet..." label if present and clear the new message field
static void clear_message_field(GtkWidget *messaging_label, GtkWidget *new_message_field)
{
    if (messaging_label)
    {
        gtk_widget_destroy(messaging_label);
        messaging_label = gtk_label_new("No messages here yet...");
    }
    gtk_entry_set_text(new_message_field, ""); // Clear the new message field
}

// Function to send the message to the server and add it to the chat interface if successful
static bool send_message_to_server(gchar *new_message)
{
    return handle_send_msg_req(new_message) == R_SUCCESS;
}

// Function to handle send button click
void send_button_click(GtkWidget *widget, gpointer new_message_field)
{
    if (widget)
    { }

    GtkWidget *chat_container, *messaging_label;

    // Find necessary widgets for sending messages
    find_send_message_widgets(&chat_container, &messaging_label);

    // Retrieve the new message from the new message field
    gchar new_message[2048];
    sprintf(new_message, "%s", gtk_entry_get_text(new_message_field));

    // Check if the new message is empty
    if (is_new_message_empty(new_message))
    {
        return;
    }

    // Remove the "No messages here yet..." label if present and clear the new message field
    clear_message_field(messaging_label, new_message_field);

    // Send the message to the server and add it to the chat interface if successful
    if (send_message_to_server(new_message))
    {
        add_message(mx_get_last_msg_node(utils->current_chat->messages));
    }
}
