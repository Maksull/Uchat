#include "../../inc/client.h"

// Function to handle signup button click
void signup_button_click(GtkWidget *widget, gpointer data)
{
    if (widget) { }
    (void)data;

    // Find necessary widgets within the main window
    GtkWidget *username_field = get_widget_by_name_r(main_window, "username_field");
    GtkWidget *username_notify_label = get_widget_by_name_r(main_window, "username_notify_label");
    GtkWidget *password_field = get_widget_by_name_r(main_window, "password_field");
    GtkWidget *password_notify_label = get_widget_by_name_r(main_window, "password_notify_label");
    GtkWidget *repassword_field = get_widget_by_name_r(main_window, "repassword_field");
    GtkWidget *repassword_notify_label = get_widget_by_name_r(main_window, "repassword_notify_label");
    GtkWidget *signup_notify_label = get_widget_by_name_r(main_window, "signup_notify_label");

    // Validate username, password, and re-entered password fields
    bool username_field_valid = validate_name_field(username_field, username_notify_label);
    bool password_field_valid = validate_password_field(password_field, password_notify_label);
    bool repassword_field_valid = validate_repassword_field(password_field, repassword_field, repassword_notify_label);

    // If any field is invalid, set error style to the signup notification label and return
    if (!username_field_valid || !password_field_valid || !repassword_field_valid)
    {
        set_notify_error_style(signup_notify_label, "Please fill all fields correctly!");
        return;
    }
    else
    {
        // If all fields are valid, set success style to the signup notification label
        set_notify_success_style(signup_notify_label, "");
    }

    // Get username and password entered by the user
    char *user_name = (char *)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(username_field)));
    char *user_password = (char *)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(password_field)));

    int response_code = handle_signup_req(user_name, user_password); // Handle the signup request and get the response code
    handle_signup_res_code(response_code, signup_notify_label);     // Handle the signup response code and update the signup notification label accordingly
}
