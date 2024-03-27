#include "../../inc/client.h"

// Function to handle edit chat response code
void handle_edit_chat_response_code(int response_code, GtkWidget* entry_field, GtkWidget *change_chat_name_notify_label)
{
    switch (response_code)
    {
        case R_SUCCESS:
            set_notify_success_style(change_chat_name_notify_label, "");

            GtkWidget *toplevel = gtk_widget_get_toplevel(change_chat_name_notify_label);
            gtk_widget_destroy(toplevel);

            update_chatlist();

            GtkWidget *chat_header_title = get_widget_by_name_r(main_window, "chat_header_title");
            gtk_label_set_text(GTK_LABEL(chat_header_title), utils->current_chat->name);
            break;

        case R_CHAT_NOENT:
            set_field_error_style(entry_field);
            set_notify_error_style(change_chat_name_notify_label, get_response_str(R_CHAT_NOENT));
            break;

        case R_NAME_LEN_INVALID:
            set_field_error_style(entry_field);
            set_notify_error_style(change_chat_name_notify_label, get_response_str(R_NAME_LEN_INVALID));
            break;

        case R_NAME_FORMAT_INVALID:
            set_field_error_style(entry_field);
            set_notify_error_style(change_chat_name_notify_label, get_response_str(R_NAME_FORMAT_INVALID));
            break;

        case R_CHAT_EXISTS:
            set_field_error_style(entry_field);
            set_notify_error_style(change_chat_name_notify_label, get_response_str(R_CHAT_EXISTS));
            break;

        default:
            break;
    }
}
