#include "../inc/client.h"

// Function to create popup window
GtkWidget *create_popup_window(int width, int height)
{
    GtkWidget*  popup_window = gtk_window_new(GTK_WINDOW_TOPLEVEL); // Create a new top-level window to serve as the popup
    // Set properties for the popup window
    gtk_widget_set_name(GTK_WIDGET(popup_window), "popup_window");
    gtk_window_set_default_size(GTK_WINDOW(popup_window), width, height);
    gtk_window_set_transient_for(GTK_WINDOW(popup_window), GTK_WINDOW(main_window));
    gtk_window_set_skip_taskbar_hint(GTK_WINDOW(popup_window), TRUE);
    gtk_window_set_position(GTK_WINDOW(popup_window), GTK_WIN_POS_CENTER_ON_PARENT);
    gtk_window_set_decorated(GTK_WINDOW(popup_window), FALSE);
    add_class(popup_window, "popup_window");
    g_signal_connect(G_OBJECT(popup_window), "focus-out-event", G_CALLBACK(destroy_popup_window), NULL); // Connect the "focus-out-event" signal to the destroy_popup_window callback function

    return popup_window; // Return the newly created popup window
}
