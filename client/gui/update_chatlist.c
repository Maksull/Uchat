#include "../inc/client.h"

// Function to update chatlist
void update_chatlist()
{
    t_chat *chatlist = utils->chatlist; // Retrieve the chat list from the application state

    if (mx_chat_list_size(chatlist) == 0) // Check if the chat list is empty
    {
        // If the chat list is empty, display a message prompting the user to join a chat to start messaging
        build_chatlist_message("Join to chat to start messaging");
        build_start_messaging_label();
    }
    else
    {
        GtkWidget *chatlist_container = get_widget_by_name_r(main_window, "chatlist"); // If the chat list is not empty, update the chat list with the latest chat information
        clear_container(chatlist_container);                                           // Clear the existing chat list container

        while (chatlist) // Iterate through each chat in the chat list and add it to the chat list container
        {
            add_chatlist_item(chatlist->id, chatlist->name, chatlist->avatar_color);
            chatlist = chatlist->next;
        }

        if (utils->current_chat) // Check if there is a current chat selected
        {
            set_chatlist_item_active(get_widget_by_name_r(chatlist_container, utils->current_chat->name)); // If there is a current chat selected, set the corresponding chat list item as active
        }
        else
        {
            build_start_messaging_label(); // If there is no current chat selected, display a message prompting the user to start messaging
        }
    }
}
