#include "../inc/client.h"

// Function to build rightbar
void build_rightbar(GtkWidget *chat_screen)
{
    GtkWidget *chat = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); // Create a vertical box widget to serve as the right sidebar
    // Set expand properties to fill available horizontal and vertical space
    gtk_widget_set_hexpand(chat, TRUE);
    gtk_widget_set_vexpand(chat, TRUE);
    gtk_widget_set_size_request(GTK_WIDGET(chat), WINDOW_WIDTH - LEFT_BAR_W, WINDOW_HEIGHT); // Set size request to occupy remaining width of window after subtracting left sidebar width
    gtk_grid_attach(GTK_GRID(chat_screen), chat, 1, 0, 2, 1); // Attach chat widget to chat_screen grid at row 0, columns 1 and 2
    // Assign a name and CSS classes to the chat widget
    gtk_widget_set_name(chat, "chat");
    add_class(chat, "chat");

    // build_start_messaging_label();
}
