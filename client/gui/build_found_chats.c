#include "../inc/client.h"

// Function to build found chats
void build_found_chats(t_chat *chat_list)
{
    GtkWidget *chatlist_container = get_widget_by_name_r(main_window, "chatlist"); // Retrieve the chatlist container widget

    // Check if there are any chats found
    if (!chat_list)
    {
        build_chatlist_message(get_response_str(R_CHAT_NOENT)); // If no chats found, display a message indicating the absence of chats
    }
    else
    {
        clear_container(chatlist_container); // If chats are found, clear the chatlist container and populate it with the found chats

        // Iterate through the list of found chats and add them to the chatlist container
        while (chat_list)
        {
            add_join_chat_item(chat_list->id, chat_list->name, chat_list->avatar_color);
            chat_list = chat_list->next;
        }
    }
}
