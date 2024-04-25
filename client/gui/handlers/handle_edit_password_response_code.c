#include "../../inc/client.h"

// Function to handle successful password edit
static void handle_successful_password_edit(GtkWidget *change_password_notify_label)
{
    set_notify_success_style(change_password_notify_label, "");
    GtkWidget *toplevel = gtk_widget_get_toplevel(change_password_notify_label);
    gtk_widget_destroy(toplevel);
}

// Function to handle invalid password response
static void handle_invalid_password(GtkWidget *entry_field, GtkWidget *change_password_notify_label)
{
    set_field_error_style(entry_field);
    set_notify_error_style(change_password_notify_label, get_res_str(R_INVALID_PASS));
}

// Function to handle invalid password length response
static void handle_invalid_password_length(GtkWidget *entry_field, GtkWidget *change_password_notify_label)
{
    set_field_error_style(entry_field);
    set_notify_error_style(change_password_notify_label, get_res_str(R_PASS_LEN_INVALID));
}

// Function to handle edit password response code
void handle_edit_password_response_code(int response_code, GtkWidget *entry_field, GtkWidget *change_password_notify_label)
{
    switch (response_code)
    {
    case R_SUCCESS:
        handle_successful_password_edit(change_password_notify_label);
        break;

    case R_INVALID_PASS:
        handle_invalid_password(entry_field, change_password_notify_label);
        break;

    case R_PASS_LEN_INVALID:
        handle_invalid_password_length(entry_field, change_password_notify_label);
        break;

    default:
        break;
    }
}
