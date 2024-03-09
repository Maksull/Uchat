#include "../inc/client.h"

// Function to destroy popup window
void destroy_popup_window(GtkWidget *widget, gpointer chat_screen)
{
    if(widget){}
    (void)chat_screen;

    // Get the top-level container of the widget (the popup window) and destroy it
    GtkWidget *popup_window = gtk_widget_get_toplevel(widget);
    gtk_widget_destroy(popup_window);
}
