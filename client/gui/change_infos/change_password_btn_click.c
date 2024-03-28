#include "../../inc/client.h"

// Function to handle change password button click
void change_password_btn_click(GtkWidget *widget, gpointer data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget); // Get the top-level window containing the widget
    (void)data;

    // Find the necessary widgets for current password, new password, and re-enter new password fields, and their corresponding notification labels
    GtkWidget *current_password_field = get_widget_by_name_r(toplevel, "current_password_field");
    GtkWidget *current_password_notify_label = get_widget_by_name_r(toplevel, "current_password_notify_label");
    GtkWidget *new_password_field = get_widget_by_name_r(toplevel, "new_password_field");
    GtkWidget *new_password_notify_label = get_widget_by_name_r(toplevel, "new_password_notify_label");
    GtkWidget *re_new_password_field = get_widget_by_name_r(toplevel, "re_new_password_field");
    GtkWidget *re_new_password_notify_label = get_widget_by_name_r(toplevel, "re_new_password_notify_label");

    // Validate the content of the current password field
    bool current_password_field_valid = validate_password_field(current_password_field, current_password_notify_label);

    char *current_password = (char *)gtk_entry_get_text(GTK_ENTRY(current_password_field));

    // If current password validation succeeds, compare it with the user's actual password
    if (current_password_field_valid)
    {
        if (mx_strcmp(current_password, utils->current_user->password) != 0)
        {
            // If passwords don't match, set error style and display error message
            set_field_error_style(current_password_field);
            set_notify_error_style(current_password_notify_label, "Incorrect password");
        }
        else
        {
            // If passwords match, set success style and clear the notification message
            set_field_success_style(current_password_field);
            set_notify_success_style(current_password_notify_label, "");
        }
    }

    // Validate the content of the new password and re-enter new password fields
    bool new_password_field_valid = validate_password_field(new_password_field, new_password_notify_label);
    bool re_new_password_field_valid = validate_repassword_field(new_password_field, re_new_password_field, re_new_password_notify_label);

    // If any of the fields fail validation, return without further action
    if (!current_password_field_valid || !new_password_field_valid || !re_new_password_field_valid)
    {
        return;
    }

    char *new_password = (char *)gtk_entry_get_text(GTK_ENTRY(new_password_field)); // Get the new password entered by the user

    // Send request to update user's password and handle the response
    int response_code = handle_edit_password_request(new_password, current_password);
    handle_edit_password_response_code(response_code, new_password_field, new_password_notify_label);
}
