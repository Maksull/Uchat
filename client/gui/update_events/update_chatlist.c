#include "../../inc/client.h"

// Function to handle the case when the chat list is empty
static void handle_empty_chatlist()
{
    build_chatlist_message("Join a chat to start messaging");
    build_start_messaging_label();
}

// Function to update the chat list container with the latest chat information
static void update_chatlist_container(t_chat *chatlist)
{
    GtkWidget *chatlist_container = get_widget_by_name_r(main_window, "chatlist"); // Get the chat list container widget
    clear_container(chatlist_container);                                           // Clear the existing chat list container

    // Iterate through each chat in the chat list and add it to the chat list container
    while (chatlist)
    {
        add_chatlist_item(chatlist->id, chatlist->name, chatlist->avatar_color);
        chatlist = chatlist->next;
    }
}

// Function to handle setting the active chat list item or displaying start messaging label
static void handle_active_chatlist_or_start_messaging_label()
{
    if (utils->current_chat)
    {
        // If there is a current chat selected, set the corresponding chat list item as active
        set_chatlist_item_active(get_widget_by_name_r(main_window, utils->current_chat->name));
    }
    else
    {
        build_start_messaging_label(); // If there is no current chat selected, display a message prompting the user to start messaging
    }
}

// Function to update the chatlist
void update_chatlist()
{
    t_chat *chatlist = utils->chatlist; // Retrieve the chat list from the application state

    if (mx_chat_list_size(chatlist) == 0)
    {
        handle_empty_chatlist(); // If the chat list is empty, handle accordingly
    }
    else
    {
        update_chatlist_container(chatlist); // If the chat list is not empty, update the chat list container with the latest chat information

        handle_active_chatlist_or_start_messaging_label(); // Handle setting the active chat list item or displaying start messaging label based on the current chat
    }
}
