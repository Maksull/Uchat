#include "../../inc/client.h"

// Function to handle delete account button click
void delete_account_btn_click(GtkWidget *widget, gpointer data)
{
    if (widget) { }
    (void)data;

    // Check if the account deletion request is successful
    if (handle_delete_account_request() == R_SUCCESS)
    {
        client_cleanup(false);        // Clean up client-side resources without exiting the application
        build_authorization_window(); // Rebuild the authorization window for the user to log in or create a new account
    }
}
