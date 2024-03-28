#include "../../inc/client.h"

// Function to handle edit button click
void edit_button_click(GtkWidget *widget, t_msg *message)
{
    if (widget) { }

    // Retrieve necessary widgets
    GtkWidget *new_message_field = get_widget_by_name_r(main_window, "new_message_field");
    GtkWidget *send_btn = get_widget_by_name_r(main_window, "send_btn");
    GtkWidget *chat_container = get_widget_by_name_r(main_window, "chat");

    // Get the new message text
    gchar new_message[2048];
    sprintf(new_message, "%s", gtk_entry_get_text(GTK_ENTRY(new_message_field)));

    // Check if the new message is empty
    if (!new_message[0])
    {
        // If empty, delete the message and return
        delete_message(NULL, NULL, message);
        return;
    }

    gtk_entry_set_text(GTK_ENTRY(new_message_field), ""); // Clear the message input field

    // Unblock the send button signal and disconnect the edit button signals to prevent recursive calls
    g_signal_handler_unblock(send_btn, g_signal_handler_find(send_btn, G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)send_button_click, NULL));
    g_signal_handler_disconnect(send_btn, g_signal_handler_find(send_btn, G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)edit_button_click, NULL));
    g_signal_handler_disconnect(new_message_field, g_signal_handler_find(new_message_field, G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)edit_button_click, NULL));
    g_signal_handler_unblock(new_message_field, g_signal_handler_find(new_message_field, G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)send_button_click, NULL));
    // gtk_button_set_label(GTK_BUTTON(send_btn), "S");

    handle_edit_msg_request(message->message_id, new_message); // Handle the request to edit the message

    update_chat_field(); // Update the chat field to reflect the changes

    gtk_widget_show_all(chat_container); // Show all widgets in the chat container
}
