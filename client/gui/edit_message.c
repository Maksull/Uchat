#include "../inc/client.h"

// Function to handle edit button
void edit_message(GtkWidget *widget, GdkEventButton *event, t_msg *message)
{
    if (widget) { }
    (void)event;

    // Retrieve necessary widgets
    GtkWidget *new_message_field = get_widget_by_name_r(main_window, "new_message_field");
    GtkWidget *send_btn = get_widget_by_name_r(main_window, "send_btn");

    gtk_entry_set_text(GTK_ENTRY(new_message_field), message->text); // Set the message input field with the current text of the selected message

    g_signal_handler_block(widget, g_signal_handler_find(widget, G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)edit_message, NULL)); // Block the edit message signal to prevent recursive calls

    // Block the send button signal and connect the message input field and send button to the edit button click handler
    g_signal_handler_block(send_btn, g_signal_handler_find(send_btn, G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)send_button_click, NULL));
    g_signal_handler_block(new_message_field, g_signal_handler_find(new_message_field, G_SIGNAL_MATCH_FUNC, 0, 0, NULL, (gpointer)send_button_click, NULL));
    g_signal_connect(new_message_field, "activate", G_CALLBACK(edit_button_click), message);
    g_signal_connect(send_btn, "clicked", G_CALLBACK(edit_button_click), message);
}
