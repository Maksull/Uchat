#include "../inc/client.h"

// Function to validate repassword field
bool validate_repassword_field(GtkWidget *password_field, GtkWidget *repassword_field, GtkWidget *repassword_notify_label)
{
    // Get the text from the password and re-entered password fields
    char *user_password = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(password_field)));
    char *user_repassword = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(repassword_field)));

    if (!mx_strcmp(user_repassword, "")) // Check for empty input
    {
        set_field_error_style(repassword_field);
        set_notify_error_style(repassword_notify_label, "Fill the password please!");
        return false; // Invalid input
    }
    else if (mx_strcmp(user_password, user_repassword)) // Check if re-entered password matches original password
    {
        set_field_error_style(repassword_field);
        set_notify_error_style(repassword_notify_label, "Passwords do not match!");
        return false; // Invalid input
    }
    else
    {
        // Input passed all validations, apply success style to field and clear notification label
        set_field_success_style(repassword_field);
        set_notify_success_style(repassword_notify_label, "");
        return true; // Valid input
    }
}
