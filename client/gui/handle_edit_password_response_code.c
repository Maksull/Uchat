#include "../inc/client.h"

// Function to handle edit password response code
void handle_edit_password_response_code(int response_code, GtkWidget* entry_field, GtkWidget *change_password_notify_label)
{
    switch (response_code)
    {
        case R_SUCCESS:
            set_notify_success_style(change_password_notify_label, "");
            GtkWidget *toplevel = gtk_widget_get_toplevel(change_password_notify_label);
            gtk_widget_destroy(toplevel);
            break;

        case R_INVALID_PASS:
            set_field_error_style(entry_field);
            set_notify_error_style(change_password_notify_label, get_response_str(R_INVALID_PASS));
            break;

        case R_PASS_LEN_INVALID:
            set_field_error_style(entry_field);
            set_notify_error_style(change_password_notify_label, get_response_str(R_PASS_LEN_INVALID));
            break;

        default:
            break;
    }
}
