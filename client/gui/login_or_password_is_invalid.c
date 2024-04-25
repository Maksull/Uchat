#include "../inc/client.h"

// Function to handle login or password being invalid
static void handle_invalid_login_or_password(GtkWidget *username_field, GtkWidget *username_notify_label,
                                      GtkWidget *password_field, GtkWidget *password_notify_label)
{
    // Set error styles and error messages for both username and password fields
    set_field_error_style(username_field);
    set_notify_error_style(username_notify_label, "Login or password is invalid");
    set_field_error_style(password_field);
    set_notify_error_style(password_notify_label, "Login or password is invalid");
}

// Function to handle login or password are invalid
void login_or_password_is_invalid(GtkWidget *login_notify_label)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel(login_notify_label); // Get the top-level window widget

    // Get widgets for username field, username notification label, password field, and password notification label
    GtkWidget *username_field = get_widget_by_name_r(toplevel, "username_field");
    GtkWidget *username_notify_label = get_widget_by_name_r(toplevel, "username_notify_label");
    GtkWidget *password_field = get_widget_by_name_r(toplevel, "password_field");
    GtkWidget *password_notify_label = get_widget_by_name_r(toplevel, "password_notify_label");

    // Handle invalid login or password
    handle_invalid_login_or_password(username_field, username_notify_label, password_field, password_notify_label);
}
