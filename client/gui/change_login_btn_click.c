#include "../inc/client.h"

// Function to handle change login btn click
void change_login_btn_click(GtkWidget *widget, gpointer data) {
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget); // Get the top-level window containing the widget
    (void)data;

    // Find the login field and the corresponding notification label within the top-level window
    GtkWidget *login_field = get_widget_by_name_r(toplevel, "login_field");
    GtkWidget *login_notify_label = get_widget_by_name_r(toplevel, "login_notify_label");

    // Validate the new login; if it's invalid, return
    if (!validate_name_field(login_field, login_notify_label)) {
        return;
    }

    char *new_login = (char*)gtk_entry_get_text(GTK_ENTRY(login_field));  // Get the new login entered by the user

    int response_code = handle_edit_username_request(new_login); // Send a request to edit the username and get the response code
    handle_edit_username_response_code(response_code, login_field, login_notify_label); // Handle the response code and update the UI accordingly

    // If the username change was successful, update the username in the leftbar footer
    if (response_code == R_SUCCESS)
    {
        GtkWidget *leftbar_footer_username = get_widget_by_name_r(main_window, "leftbar_footer_username");
        gtk_label_set_text(GTK_LABEL(leftbar_footer_username), utils->current_user->name);
    }
}
