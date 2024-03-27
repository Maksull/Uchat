#include "../../inc/client.h"

// Function to handle edit username response code
void handle_edit_username_response_code(int response_code, GtkWidget* entry_field, GtkWidget *change_login_notify_label)
{
    switch (response_code)
    {
        case R_SUCCESS:
            set_notify_success_style(change_login_notify_label, "");
            GtkWidget *toplevel = gtk_widget_get_toplevel(change_login_notify_label);
            gtk_widget_destroy(toplevel);
            break;

        case R_USR_EXISTS:
            set_field_error_style(entry_field);
            set_notify_error_style(change_login_notify_label, get_response_str(R_USR_EXISTS));
            break;

        case R_NAME_LEN_INVALID:
            set_field_error_style(entry_field);
            set_notify_error_style(change_login_notify_label, get_response_str(R_NAME_LEN_INVALID));
            break;

        case R_NAME_FORMAT_INVALID:
            set_field_error_style(entry_field);
            set_notify_error_style(change_login_notify_label, get_response_str(R_NAME_FORMAT_INVALID));
            break;

        default:
            break;
    }
}
