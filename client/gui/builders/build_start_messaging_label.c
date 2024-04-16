#include "../../inc/client.h"

// Function to create a label widget with a given message
static GtkWidget *create_label(const gchar *message)
{
    GtkWidget *label = gtk_label_new(message);
    gtk_widget_set_halign(GTK_WIDGET(label), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(label), GTK_ALIGN_CENTER);
    gtk_widget_set_vexpand(label, TRUE);
    gtk_widget_set_hexpand(label, TRUE);
    add_class(label, "chatscreen_notify");

    return label;
}

// Function to build start messaging label
void build_start_messaging_label()
{
    GtkWidget *chat_container = get_widget_by_name_r(main_window, "chat"); // Get the chat container widget

    clear_container(chat_container); // Clear the chat container

    // Create a new label widget with a message prompting the user to select a chat
    GtkWidget *messaging_label = create_label("Select a chat to start messaging");

    // Pack the label into the chat container
    gtk_box_pack_start(GTK_BOX(chat_container), messaging_label, FALSE, FALSE, 0);

    gtk_widget_show_all(chat_container); // Show all widgets within the chat container
}
