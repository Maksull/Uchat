#include "../../inc/client.h"

// Function to validate if the password is not empty
static bool is_password_not_empty(char *password)
{
    return mx_strcmp(password, "") != 0;
}

// Function to validate if the password length is within the specified range
static bool is_password_length_valid(char *password)
{
    size_t password_length = mx_strlen(password);
    return password_length >= MIN_PASS_INPUT_LEN && password_length <= MAX_PASS_INPUT_LEN;
}

// Function to set error style and notification for an invalid password
static void handle_invalid_password(GtkWidget *password_field, GtkWidget *password_notify_label, char *error_message)
{
    set_field_error_style(password_field);
    set_notify_error_style(password_notify_label, error_message);
}

// Function to set success style and clear notification for a valid password
static void handle_valid_password(GtkWidget *password_field, GtkWidget *password_notify_label)
{
    set_field_success_style(password_field);
    set_notify_success_style(password_notify_label, "");
}

// Function to validate password field
bool validate_password_field(GtkWidget *password_field, GtkWidget *password_notify_label)
{
    char *user_password = (char *)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(password_field)));

    if (!is_password_not_empty(user_password))
    {
        handle_invalid_password(password_field, password_notify_label, "Fill the password please!");

        return false;
    }
    else if (!is_password_length_valid(user_password))
    {
        handle_invalid_password(password_field, password_notify_label, "Password length must be between 8 and 30 characters");
        
        return false;
    }
    else
    {
        handle_valid_password(password_field, password_notify_label);
        
        return true;
    }
}
