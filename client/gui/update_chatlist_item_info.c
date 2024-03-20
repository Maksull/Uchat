#include "../inc/client.h"

// Update information of a chat list item
void update_chatlist_item_info(t_chat *chat)
{
    GtkWidget *chatlist_container = get_widget_by_name_r(main_window, "chatlist"); // Get chat list container
    GtkWidget *chatlist_item = get_widget_by_name_r(chatlist_container, chat->name); // Get chat list item widget

    // Prepare text and date information for the chat list item
    char *text = chat->last_new_msg ? ellipsis_str(chat->last_new_msg->text, 16) : mx_strdup("No messages yet");
    char *date_str = chat->last_new_msg ? chat->last_new_msg->date_str : "";
    int new_msg_count = chat ? chat->new_msg_count : 0;

    // Get widgets for message, time, and notification count of the chat list item
    GtkWidget *chatlist_item_message = get_widget_by_name_r(chatlist_item, "chatlist_item_message");
    GtkWidget *chatlist_item_time = get_widget_by_name_r(chatlist_item, "chatlist_item_time");
    GtkWidget *chatlist_item_notify = get_widget_by_name_r(chatlist_item, "chatlist_item_notify");

    // Set text and date information for message and time labels
    gtk_label_set_text(GTK_LABEL(chatlist_item_message), text);
    gtk_label_set_text(GTK_LABEL(chatlist_item_time), date_str);

    if (new_msg_count > 0) // If there are new messages
    {
        gtk_label_set_text(GTK_LABEL(chatlist_item_notify), mx_itoa(new_msg_count)); // Set new message count text
        add_class(chatlist_item_notify, "chatlist_item_notify--visible"); // Add class to make notification visible
    }
    else // If there are no new messages
    {
        remove_class(chatlist_item_notify, "chatlist_item_notify--visible"); // Remove class to hide notification
    }
    mx_strdel(&text); // Free memory allocated for text
}
