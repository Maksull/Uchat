#include "../../inc/client.h"

// Function to handle successful chat creation
static void handle_successful_chat_creation(GtkWidget *entry_field, GtkWidget *create_chat_notify_label)
{
    set_notify_success_style(create_chat_notify_label, "");

    GtkWidget *chatlist_container = get_widget_by_name_r(main_window, "chatlist");
    GtkWidget *toplevel = gtk_widget_get_toplevel(entry_field);
    update_chatlist();
    if (utils->current_chat)
    {
        set_chatlist_item_active(get_widget_by_name_r(chatlist_container, utils->current_chat->name));
    }
    gtk_widget_destroy(toplevel);
}

// Function to handle chat already exists response
static void handle_chat_already_exists(GtkWidget *entry_field, GtkWidget *create_chat_notify_label)
{
    set_field_error_style(entry_field);
    set_notify_error_style(create_chat_notify_label, get_res_str(R_CHAT_EXISTS));
}

// Function to handle maximum chats reached response
static void handle_max_chats_reached(GtkWidget *entry_field, GtkWidget *create_chat_notify_label)
{
    set_field_error_style(entry_field);
    set_notify_error_style(create_chat_notify_label, get_res_str(R_CHATS_TOTAL_REACHED));
}

// Function to handle create chat response code
void handle_create_chat_response_code(int response_code, GtkWidget *entry_field, GtkWidget *create_chat_notify_label)
{
    switch (response_code)
    {
    case R_SUCCESS:
        handle_successful_chat_creation(entry_field, create_chat_notify_label);
        break;

    case R_CHAT_EXISTS:
        handle_chat_already_exists(entry_field, create_chat_notify_label);
        break;

    case R_CHATS_TOTAL_REACHED:
        handle_max_chats_reached(entry_field, create_chat_notify_label);
        break;

    default:
        break;
    }
}
