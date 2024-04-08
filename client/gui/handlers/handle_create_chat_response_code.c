#include "../../inc/client.h"

// Function to handle create chat response code
void handle_create_chat_response_code(int response_code, GtkWidget* entry_field, GtkWidget *create_chat_notify_label)
{
    switch (response_code)
    {
        case R_SUCCESS:
            set_notify_success_style(create_chat_notify_label, "");

            GtkWidget *chatlist_container = get_widget_by_name_r(main_window, "chatlist");
            GtkWidget *toplevel = gtk_widget_get_toplevel(entry_field);
            update_chatlist();
            utils->current_chat ? set_chatlist_item_active(get_widget_by_name_r(chatlist_container, utils->current_chat->name)) : (void)0;
            gtk_widget_destroy(toplevel);
            break;

        case R_CHAT_EXISTS:
            set_field_error_style(entry_field);
            set_notify_error_style(create_chat_notify_label, get_res_str(R_CHAT_EXISTS));
            break;

        case R_CHATS_TOTAL_REACHED:
            set_field_error_style(entry_field);
            set_notify_error_style(create_chat_notify_label, get_res_str(R_CHATS_TOTAL_REACHED));
            break;

        default:
            break;
    }
}
