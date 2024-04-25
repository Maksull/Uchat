#include "../../inc/client.h"

// Function to prepare text for the chat list item
static char *prepare_chatlist_item_text(t_msg *last_new_msg)
{
    if (last_new_msg)
    {
        return ellipsis_str(last_new_msg->text, 16);
    }
    else
    {
        return mx_strdup("No messages yet");
    }
}

// Function to prepare date string for the chat list item
static char *prepare_chatlist_item_date(t_msg *last_new_msg)
{
    if (last_new_msg)
    {
        return last_new_msg->date_str;
    }
    else
    {
        return "";
    }
}

// Function to update the notification count of the chat list item
static void update_chatlist_item_notify_count(GtkWidget *chatlist_item_notify, int new_msg_count)
{
    if (new_msg_count > 0)
    {
        gtk_label_set_text(GTK_LABEL(chatlist_item_notify), mx_itoa(new_msg_count));
        add_class(chatlist_item_notify, "chatlist_item_notify--visible");
    }
    else
    {
        remove_class(chatlist_item_notify, "chatlist_item_notify--visible");
    }
}

// Function to update the labels of a chat list item
static void update_chatlist_item_labels(GtkWidget *chatlist_item, const char *message_text, const char *time_text)
{
    // Get widgets for message, time, and notification count of the chat list item
    GtkWidget *chatlist_item_message = get_widget_by_name_r(chatlist_item, "chatlist_item_message");
    GtkWidget *chatlist_item_time = get_widget_by_name_r(chatlist_item, "chatlist_item_time");

    // Set text for message and time labels
    gtk_label_set_text(GTK_LABEL(chatlist_item_message), message_text);
    gtk_label_set_text(GTK_LABEL(chatlist_item_time), time_text);
}

// Function to update information of a chat list item
void update_chatlist_item_info(t_chat *chat)
{
    GtkWidget *chatlist_container = get_widget_by_name_r(main_window, "chatlist");   // Get chat list container
    GtkWidget *chatlist_item = get_widget_by_name_r(chatlist_container, chat->name); // Get chat list item widget

    // Prepare text and date information for the chat list item
    char *text = prepare_chatlist_item_text(chat->last_new_msg);
    char *date_str = prepare_chatlist_item_date(chat->last_new_msg);
    int new_msg_count = chat ? chat->new_msg_count : 0;

    // Update the labels of the chat list item
    update_chatlist_item_labels(chatlist_item, text, date_str);

    // Get widget for the notification count of the chat list item
    GtkWidget *chatlist_item_notify = get_widget_by_name_r(chatlist_item, "chatlist_item_notify");

    // Update the notification count
    update_chatlist_item_notify_count(chatlist_item_notify, new_msg_count);

    mx_strdel(&text); // Free memory allocated for text
}
