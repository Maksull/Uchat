#include "../inc/client.h"

// Function to destroy main window
void destroy(GtkWidget *widget, gpointer data)
{
    if (widget) { }
    (void)data;

    pthread_cancel(utils->th_reader); // Cancel the thread responsible for reading server updates
    handle_logout_req(true);      // Handle the logout request with a flag indicating forced logout
    client_cleanup(true);             // Clean up client resources with a flag indicating forced cleanup
    gtk_main_quit();                  // Quit the GTK main loop
}
