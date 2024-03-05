#include "../inc/client.h"

// Update the chat field with messages
void update_chat_field()
{
    GtkWidget *chat_field = get_widget_by_name_r(main_window, "chat_field"); // Get chat field widget

    clear_container(chat_field); // Clear the chat field

    t_msg *messages = utils->current_chat->messages; // Get messages for the current chat
    if (mx_msg_list_size(messages) == 0) // Check if there are no messages
    {
        // Display a label indicating no messages
        GtkWidget *messaging_label = gtk_label_new("No messages here yet...");
        gtk_widget_set_name(messaging_label, "messaging_label");
        gtk_widget_set_halign(GTK_WIDGET(messaging_label), GTK_ALIGN_CENTER);
        gtk_widget_set_valign(GTK_WIDGET(messaging_label), GTK_ALIGN_CENTER);
        gtk_widget_set_vexpand(messaging_label, TRUE);
        gtk_widget_set_hexpand(messaging_label, TRUE);
        gtk_box_pack_start(GTK_BOX(chat_field), messaging_label, FALSE, FALSE, 0);
    }
    else
    {
        // Add each message to the chat field
        while (messages)
        {
            add_message(messages);
            messages = messages->next;
        }
    }

    gtk_widget_show_all(chat_field); // Show all widgets in the chat field
}
