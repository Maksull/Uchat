#include "../../inc/client.h"

// Function to build start messaging label
void build_start_messaging_label()
{
    GtkWidget *chat_container = get_widget_by_name_r(main_window, "chat"); // Get the chat container widget

    clear_container(chat_container); // Clear the chat container

    // Create a new label widget with a message prompting the user to select a chat
    GtkWidget *messaging_label = gtk_label_new("Select a chat to start messaging");
    gtk_widget_set_halign(GTK_WIDGET(messaging_label), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(messaging_label), GTK_ALIGN_CENTER);
    gtk_widget_set_vexpand(messaging_label, TRUE);
    gtk_widget_set_hexpand(messaging_label, TRUE);
    add_class(messaging_label, "chatscreen_notify");

    gtk_box_pack_start(GTK_BOX(chat_container), messaging_label, FALSE, FALSE, 0); // Pack the label into the chat container

    gtk_widget_show_all(chat_container); // Show all widgets within the chat container
}
