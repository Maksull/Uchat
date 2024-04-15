#include "../../inc/client.h"

// Function to find necessary widgets within the top-level window for focusing out current password field
void find_password_widgets(GtkWidget *toplevel, GtkWidget **current_password_field, GtkWidget **current_password_notify_label)
{
    *current_password_field = get_widget_by_name_r(toplevel, "current_password_field");
    *current_password_notify_label = get_widget_by_name_r(toplevel, "current_password_notify_label");
}

// Function to validate the content of the current password field and compare it with the user's current password
void validate_current_password(GtkWidget *current_password_field, GtkWidget *current_password_notify_label)
{
    if (validate_password_field(current_password_field, current_password_notify_label))
    {
        char *current_password = (char *)gtk_entry_get_text(GTK_ENTRY(current_password_field)); // Get the current password entered by the user
        // Compare the entered password with the user's current password
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
}

// Function to focus out current password field
void focus_out_current_password_field(GtkWidget *widget, gpointer data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget); // Get the top-level window containing the widget
    (void)data;

    // Find the current password field and the corresponding notification label within the top-level window
    GtkWidget *current_password_field, *current_password_notify_label;
    find_password_widgets(toplevel, &current_password_field, &current_password_notify_label);

    // Validate the content of the current password field and compare it with the user's current password
    validate_current_password(current_password_field, current_password_notify_label);
}
