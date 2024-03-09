#include "../inc/client.h"

// Function to validate name field
bool validate_name_field(GtkWidget *username_field, GtkWidget *username_notify_label)
{
    char *user_name = (char *)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(username_field))); // Get the text from the name field

    // Check for empty input
    if (!mx_strcmp(user_name, ""))
    {
        set_field_error_style(username_field);
        set_notify_error_style(username_notify_label, "Fill the name please!");
        return false; // Invalid input
    }
    else if (mx_strlen(user_name) < MIN_NAME_INPUT_LEN) // Check for minimum length
    {
        set_field_error_style(username_field);
        set_notify_error_style(username_notify_label, "The name length must be at least 4 characters");
        return false; // Invalid input
    }
    else if (mx_strlen(user_name) > MAX_NAME_INPUT_LEN) // Check for maximum length
    {
        set_field_error_style(username_field);
        set_notify_error_style(username_notify_label, "The name length must not exceed 16 characters");
        return false; // Invalid input
    }
    else if (!is_user_name_format_valid(user_name)) // Check for valid name format
    {
        set_field_error_style(username_field);
        set_notify_error_style(username_notify_label, get_response_str(R_NAME_FORMAT_INVALID));
        return false; // Invalid input
    }
    else
    {
        // Input passed all validations, apply success style to field and clear notification label
        set_field_success_style(username_field);
        set_notify_success_style(username_notify_label, "");
        return true; // Valid input
    }
}
