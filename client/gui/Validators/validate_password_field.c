#include "../../inc/client.h"

// Function to validate password field
bool validate_password_field(GtkWidget *password_field, GtkWidget *password_notify_label)
{
    char *user_password = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(password_field))); // Get the text from the password field

    // Check for empty input
    if (!mx_strcmp(user_password, ""))
    {
        set_field_error_style(password_field);
        set_notify_error_style(password_notify_label, "Fill the password please!");
        return false; // Invalid input
    }
    else if (mx_strlen(user_password) < MIN_PASS_INPUT_LEN) // Check for minimum length
    {
        set_field_error_style(password_field);
        set_notify_error_style(password_notify_label, "Password length must be at least 8 characters");
        return false; // Invalid input
    }
    else if (mx_strlen(user_password) > MAX_PASS_INPUT_LEN) // Check for maximum length
    {
        set_field_error_style(password_field);
        set_notify_error_style(password_notify_label, "Password length must not exceed 30 characters");
        return false; // Invalid input
    }
    else
    {
        // Input passed all validations, apply success style to field and clear notification label
        set_field_success_style(password_field);
        set_notify_success_style(password_notify_label, "");
        return true; // Valid input
    }
}
