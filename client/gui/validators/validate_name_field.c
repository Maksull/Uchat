#include "../../inc/client.h"

// Function to validate if the name is not empty
static bool is_name_not_empty(char *name)
{
    return mx_strcmp(name, "") != 0;
}

// Function to validate if the name length is within the specified range
static bool is_name_length_valid(char *name)
{
    size_t name_length = mx_strlen(name);
    return name_length >= MIN_NAME_INPUT_LEN && name_length <= MAX_NAME_INPUT_LEN;
}

// Function to validate if the name format is valid
static bool is_name_format_valid(char *name)
{
    return is_user_name_format_valid(name);
}

// Function to set error style and notification for an invalid name
static void handle_invalid_name(GtkWidget *username_field, GtkWidget *username_notify_label, char *error_message)
{
    set_field_error_style(username_field);
    set_notify_error_style(username_notify_label, error_message);
}

// Function to set success style and clear notification for a valid name
static void handle_valid_name(GtkWidget *username_field, GtkWidget *username_notify_label)
{
    set_field_success_style(username_field);
    set_notify_success_style(username_notify_label, "");
}

// Function to validate name field
bool validate_name_field(GtkWidget *username_field, GtkWidget *username_notify_label)
{
    char *user_name = (char *)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(username_field)));

    if (!is_name_not_empty(user_name))
    {
        handle_invalid_name(username_field, username_notify_label, "Fill the name please!");

        return false;
    }
    else if (!is_name_length_valid(user_name))
    {
        handle_invalid_name(username_field, username_notify_label, "The name length must be between 4 and 16 characters");
        
        return false;
    }
    else if (!is_name_format_valid(user_name))
    {
        handle_invalid_name(username_field, username_notify_label, get_res_str(R_NAME_FORMAT_INVALID));
        
        return false;
    }
    else
    {
        handle_valid_name(username_field, username_notify_label);
        
        return true;
    }
}
