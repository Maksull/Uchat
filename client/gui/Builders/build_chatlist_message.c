#include "../../inc/client.h"

// Function to build chatlist message
void build_chatlist_message(char *message)
{
    GtkWidget *chatlist = get_widget_by_name_r(main_window, "chatlist"); // Retrieve the chatlist widget from the main window
    clear_container(chatlist);                                           // Clear the contents of the chatlist

    // Create a label widget to display the provided message
    GtkWidget *chatlist_notify_label = gtk_label_new(message);
    gtk_widget_set_name(chatlist_notify_label, "chatlist_notify_label");
    add_class(chatlist_notify_label, "chatscreen_notify");
    gtk_widget_set_halign(GTK_WIDGET(chatlist_notify_label), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(chatlist_notify_label), GTK_ALIGN_CENTER);
    // Pack the label into the chatlist, allowing it to expand both vertically and horizontally
    gtk_box_pack_start(GTK_BOX(chatlist), chatlist_notify_label, FALSE, FALSE, 0);
    gtk_widget_set_vexpand(chatlist_notify_label, TRUE);
    gtk_widget_set_hexpand(chatlist_notify_label, TRUE);

    gtk_widget_show_all(chatlist); // Display the chatlist widget
}
