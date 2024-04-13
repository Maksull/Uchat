#include "../inc/client.h"

// Function to set the text of a message in the message input field
static void set_message_text(GtkWidget *new_message_field, const char *text)
{
    gtk_entry_set_text(GTK_ENTRY(new_message_field), text);
}

// Function to block a signal handler for a widget
static void block_signal_handler(GtkWidget *widget, const gchar *signal_name, gpointer func)
{
    g_signal_handler_block(widget, g_signal_handler_find(widget, G_SIGNAL_MATCH_FUNC, 0, 0, NULL, func, NULL));
}

// Function to connect the message input field and send button to the edit button click handler
static void connect_to_edit_button(GtkWidget *new_message_field, GtkWidget *send_btn, t_msg *message)
{
    g_signal_connect(new_message_field, "activate", G_CALLBACK(edit_button_click), message);
    g_signal_connect(send_btn, "clicked", G_CALLBACK(edit_button_click), message);
}

// Function to handle edit button
void edit_message(GtkWidget *widget, GdkEventButton *event, t_msg *message)
{
    if (widget)
    { }
    (void)event;

    // Retrieve necessary widgets
    GtkWidget *new_message_field = get_widget_by_name_r(main_window, "new_message_field");
    GtkWidget *send_btn = get_widget_by_name_r(main_window, "send_btn");

    // Set the message input field with the current text of the selected message
    set_message_text(new_message_field, message->text);

    // Block the edit message signal to prevent recursive calls
    block_signal_handler(widget, "button-press-event", (gpointer)edit_message);

    // Block the send button signal and connect the message input field and send button to the edit button click handler
    block_signal_handler(send_btn, "clicked", (gpointer)send_button_click);
    block_signal_handler(new_message_field, "activate", (gpointer)send_button_click);
    connect_to_edit_button(new_message_field, send_btn, message);
}
