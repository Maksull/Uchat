#include "../../inc/client.h"

// Function to handle successful chat edit
static void handle_successful_chat_edit(GtkWidget *change_chat_name_notify_label)
{
    set_notify_success_style(change_chat_name_notify_label, "");

    GtkWidget *toplevel = gtk_widget_get_toplevel(change_chat_name_notify_label);
    gtk_widget_destroy(toplevel);

    update_chatlist();

    GtkWidget *chat_header_title = get_widget_by_name_r(main_window, "chat_header_title");
    gtk_label_set_text(GTK_LABEL(chat_header_title), utils->current_chat->name);
}

// Function to handle chat not found response
static void handle_chat_not_found(GtkWidget *entry_field, GtkWidget *change_chat_name_notify_label)
{
    set_field_error_style(entry_field);
    set_notify_error_style(change_chat_name_notify_label, get_res_str(R_CHAT_NOENT));
}

// Function to handle invalid name length response
static void handle_invalid_name_length(GtkWidget *entry_field, GtkWidget *change_chat_name_notify_label)
{
    set_field_error_style(entry_field);
    set_notify_error_style(change_chat_name_notify_label, get_res_str(R_NAME_LEN_INVALID));
}

// Function to handle invalid name format response
static void handle_invalid_name_format(GtkWidget *entry_field, GtkWidget *change_chat_name_notify_label)
{
    set_field_error_style(entry_field);
    set_notify_error_style(change_chat_name_notify_label, get_res_str(R_NAME_FORMAT_INVALID));
}

// Function to handle chat already exists response for editing
static void handle_chat_already_exists_edit(GtkWidget *entry_field, GtkWidget *change_chat_name_notify_label)
{
    set_field_error_style(entry_field);
    set_notify_error_style(change_chat_name_notify_label, get_res_str(R_CHAT_EXISTS));
}

// Function to handle edit chat response code
void handle_edit_chat_response_code(int response_code, GtkWidget *entry_field, GtkWidget *change_chat_name_notify_label)
{
    switch (response_code)
    {
    case R_SUCCESS:
        handle_successful_chat_edit(change_chat_name_notify_label);
        break;

    case R_CHAT_NOENT:
        handle_chat_not_found(entry_field, change_chat_name_notify_label);
        break;

    case R_NAME_LEN_INVALID:
        handle_invalid_name_length(entry_field, change_chat_name_notify_label);
        break;

    case R_NAME_FORMAT_INVALID:
        handle_invalid_name_format(entry_field, change_chat_name_notify_label);
        break;

    case R_CHAT_EXISTS:
        handle_chat_already_exists_edit(entry_field, change_chat_name_notify_label);
        break;

    default:
        break;
    }
}
