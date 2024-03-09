#include "../inc/client.h"

// Function to handle login button click
void login_button_click(GtkWidget *widget, gpointer data)
{
    if(widget){}
    (void)data;

    // Find necessary widgets within the main window
    GtkWidget *username_field = get_widget_by_name_r(main_window, "username_field");
    GtkWidget *username_notify_label = get_widget_by_name_r(main_window, "username_notify_label");
    GtkWidget *password_field = get_widget_by_name_r(main_window, "password_field");
    GtkWidget *password_notify_label = get_widget_by_name_r(main_window, "password_notify_label");
    GtkWidget *login_notify_label = get_widget_by_name_r(main_window, "login_notify_label");

    // Check if the username or password field is empty
    bool username_field_is_empty = is_empty_field(username_field, username_notify_label);
    bool password_field_is_empty = is_empty_field(password_field, password_notify_label);

    // If any field is empty, return
    if (username_field_is_empty || password_field_is_empty)
    {
        return;
    }

    // Get username and password entered by the user
    char *user_name = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(username_field)));
    char *user_password = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(password_field)));

    int response_code = handle_login_request(user_name, user_password); // Handle the login request and get the response code
    handle_login_response_code(response_code, login_notify_label); // Handle the login response code and update the login notification label accordingly
}
