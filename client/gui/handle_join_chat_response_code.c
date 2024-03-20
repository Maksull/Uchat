#include "../inc/client.h"

// Function to handle join chat response code
void handle_join_chat_response_code(int response_code, char *chat_name)
{
    switch (response_code)
    {
        case R_SUCCESS: {
            GtkWidget *search_field = get_widget_by_name_r(main_window, "global_search_field");
            gtk_entry_set_text(GTK_ENTRY(search_field), "");
            GtkWidget *new_chatlist_item = get_widget_by_name_r(main_window, chat_name);
            activate_chat(new_chatlist_item);
            break;
        }

        case R_CHAT_NOENT:
            build_chatlist_message(get_response_str(R_CHAT_NOENT));
            break;

        case R_IS_CHAT_MEMBER:
            build_chatlist_message(get_response_str(R_IS_CHAT_MEMBER));
            break;

        case R_CHATS_TOTAL_REACHED:
            build_chatlist_message(get_response_str(R_CHATS_TOTAL_REACHED));
            break;

        default:
            break;
    }
}
