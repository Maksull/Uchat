#include "../../inc/client.h"

// Function to validate if the re-entered password is not empty
static bool is_repassword_not_empty(char *repassword)
{
    return mx_strcmp(repassword, "") != 0;
}

// Function to validate if the re-entered password matches the original password
static bool does_repassword_match(char *password, char *repassword)
{
    return mx_strcmp(password, repassword) == 0;
}

// Function to set error style and notification for an invalid re-entered password
static void handle_invalid_repassword(GtkWidget *repassword_field, GtkWidget *repassword_notify_label, const gchar *error_message)
{
    set_field_error_style(repassword_field);
    set_notify_error_style(repassword_notify_label, error_message);
}

// Function to set success style and clear notification for a valid re-entered password
static void handle_valid_repassword(GtkWidget *repassword_field, GtkWidget *repassword_notify_label)
{
    set_field_success_style(repassword_field);
    set_notify_success_style(repassword_notify_label, "");
}

// Function to validate the re-entered password field
bool validate_repassword_field(GtkWidget *password_field, GtkWidget *repassword_field, GtkWidget *repassword_notify_label)
{
    char *user_password = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(password_field)));
    char *user_repassword = gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(repassword_field)));

    if (!is_repassword_not_empty(user_repassword))
    {
        handle_invalid_repassword(repassword_field, repassword_notify_label, "Fill the password please!");
        
        return false;
    }
    else if (!does_repassword_match(user_password, user_repassword))
    {
        handle_invalid_repassword(repassword_field, repassword_notify_label, "Passwords do not match!");
        
        return false;
    }
    else
    {
        handle_valid_repassword(repassword_field, repassword_notify_label);
        
        return true;
    }
}
