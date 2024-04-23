#include "../../inc/client.h"

// Function to handle change avatar button click
void change_avatar_btn_click(GtkWidget *widget, gpointer data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget); // Get the top-level window containing the widget
    (void)data;

    gtk_widget_destroy(toplevel); // Destroy the top-level window
}
