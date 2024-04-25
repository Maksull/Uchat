#include "../../inc/client.h"

// Function to handle logout button click
void logout_btn_click(GtkWidget *widget, gpointer data)
{
    if (widget) { }
    (void)data;

    pthread_cancel(utils->th_reader); // Cancel the thread responsible for reading server updates
    handle_logout_req(false); // Send a logout request to the server
    client_cleanup(false); // Perform client cleanup
    pthread_create(&utils->th_reader, NULL, handle_server_updates, NULL); // Restart the thread for handling server updates
    build_authorization_window(); // Build the authorization window for logging back in or registering a new account
}
