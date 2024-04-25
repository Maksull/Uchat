#include "../../inc/client.h"

// Function to handle successful username edit
static void handle_successful_username_edit(GtkWidget *change_login_notify_label)
{
    set_notify_success_style(change_login_notify_label, "");
    GtkWidget *toplevel = gtk_widget_get_toplevel(change_login_notify_label);
    gtk_widget_destroy(toplevel);
}

// Function to handle existing username response
static void handle_existing_username(GtkWidget *entry_field, GtkWidget *change_login_notify_label)
{
    set_field_error_style(entry_field);
    set_notify_error_style(change_login_notify_label, get_res_str(R_USR_EXISTS));
}

// Function to handle invalid username length response
static void handle_invalid_username_length(GtkWidget *entry_field, GtkWidget *change_login_notify_label)
{
    set_field_error_style(entry_field);
    set_notify_error_style(change_login_notify_label, get_res_str(R_NAME_LEN_INVALID));
}

// Function to handle invalid username format response
static void handle_invalid_username_format(GtkWidget *entry_field, GtkWidget *change_login_notify_label)
{
    set_field_error_style(entry_field);
    set_notify_error_style(change_login_notify_label, get_res_str(R_NAME_FORMAT_INVALID));
}

// Function to handle edit username response code
void handle_edit_username_response_code(int response_code, GtkWidget *entry_field, GtkWidget *change_login_notify_label)
{
    switch (response_code)
    {
    case R_SUCCESS:
        handle_successful_username_edit(change_login_notify_label);
        break;

    case R_USR_EXISTS:
        handle_existing_username(entry_field, change_login_notify_label);
        break;

    case R_NAME_LEN_INVALID:
        handle_invalid_username_length(entry_field, change_login_notify_label);
        break;

    case R_NAME_FORMAT_INVALID:
        handle_invalid_username_format(entry_field, change_login_notify_label);
        break;

    default:
        break;
    }
}
