#include "../../inc/client.h"

// Function to create a new GTK window
GtkWidget *create_new_window(char *title, int width, int height, bool resizable)
{
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);             // Create a new top-level window
    gtk_window_set_title(GTK_WINDOW(window), title);                     // Set the window title
    gtk_window_set_default_size(GTK_WINDOW(window), width, height);      // Set the default size of the window
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);     // Set the window position to center
    gtk_window_set_resizable(GTK_WINDOW(window), resizable);             // Set whether the window is resizable
    g_signal_connect(window, "delete_event", G_CALLBACK(destroy), NULL); // Connect the delete event signal

    return window; // Return the created window
}
