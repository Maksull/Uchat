#include "../../inc/client.h"

// Function to handle successful join chat response
static void handle_successful_join_chat(char *chat_name)
{
    GtkWidget *search_field = get_widget_by_name_r(main_window, "global_search_field");
    gtk_entry_set_text(GTK_ENTRY(search_field), "");
    GtkWidget *new_chatlist_item = get_widget_by_name_r(main_window, chat_name);
    activate_chat(new_chatlist_item);
}

// Function to handle non-existent chat response
static void handle_nonexistent_chat()
{
    build_chatlist_message(get_res_str(R_CHAT_NOENT));
}

// Function to handle already being a member of the chat response
static void handle_already_chat_member()
{
    build_chatlist_message(get_res_str(R_IS_CHAT_MEMBER));
}

// Function to handle reaching the total number of chats response
static void handle_chats_total_reached()
{
    build_chatlist_message(get_res_str(R_CHATS_TOTAL_REACHED));
}

// Function to handle join chat response code
void handle_join_chat_response_code(int response_code, char *chat_name)
{
    switch (response_code)
    {
    case R_SUCCESS:
        handle_successful_join_chat(chat_name);
        break;

    case R_CHAT_NOENT:
        handle_nonexistent_chat();
        break;

    case R_IS_CHAT_MEMBER:
        handle_already_chat_member();
        break;

    case R_CHATS_TOTAL_REACHED:
        handle_chats_total_reached();
        break;

    default:
        break;
    }
}
