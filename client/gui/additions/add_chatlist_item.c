#include "../../inc/client.h"

// Helper function to create an event box for a chat list item
static GtkWidget *create_event_box(const char *chat_name) {
    GtkWidget *event_box = gtk_event_box_new();
    gtk_event_box_set_above_child(GTK_EVENT_BOX(event_box), TRUE);
    gtk_widget_set_name(event_box, chat_name);
    add_class(event_box, "chatlist_item_wrap");
    g_signal_connect(G_OBJECT(event_box), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(event_box), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(event_box), "button_press_event", G_CALLBACK(chatlist_item_on_click), NULL);
    return event_box;
}

// Helper function to create a drawing area for the chat avatar
static GtkWidget *create_avatar_drawing_area() {
    GtkWidget *avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 42, 42);
    gtk_widget_set_halign(avatar, GTK_ALIGN_START);
    gtk_widget_set_valign(avatar, GTK_ALIGN_CENTER);
    return avatar;
}

// Helper function to create a vertical box widget
static GtkWidget *create_vertical_box() {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(GTK_WIDGET(box), GTK_ALIGN_START);
    gtk_widget_set_valign(GTK_WIDGET(box), GTK_ALIGN_START);
    return box;
}

// Function to add a chatlist item
void add_chatlist_item(int id, char *chat_name, t_avatar_color avatar_color)
{
    GtkWidget *chatlist_container = get_widget_by_name_r(main_window, "chatlist"); // Retrieve the chatlist container widget from the main window

    // Create an event box to hold the chat list item
    GtkWidget *event_box = create_event_box(chat_name);
    gtk_box_pack_start(GTK_BOX(chatlist_container), event_box, FALSE, FALSE, 0);

    // Create a horizontal box to contain the chat list item elements
    GtkWidget *chatlist_item = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(chatlist_item, mx_itoa(id));
    add_class(chatlist_item, "chatlist_item");
    gtk_container_add(GTK_CONTAINER(event_box), chatlist_item);

    // Create a label to display the chat ID (hidden)
    GtkWidget *chatlist_item_id = gtk_label_new(mx_itoa(id)); /// CHAT ID
    gtk_widget_set_name(chatlist_item_id, "chat_id");
    add_class(chatlist_item_id, "hidden");
    gtk_box_pack_start(GTK_BOX(chatlist_item), chatlist_item_id, FALSE, FALSE, 0);

    // Create a drawing area for the chat avatar
    GtkWidget *avatar = create_avatar_drawing_area();
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_chat_avatar), (gpointer)avatar_color);
    gtk_box_pack_start(GTK_BOX(chatlist_item), avatar, FALSE, FALSE, 0);

    // Create a vertical box for the text block
    GtkWidget *chatlist_item_text = create_vertical_box();
    gtk_box_pack_start(GTK_BOX(chatlist_item), chatlist_item_text, false, false, 0);
    add_class(chatlist_item_text, "chatlist_item_text");

    // Create a label to display the chat name
    GtkWidget *chatlist_item_title = gtk_label_new(chat_name);
    add_class(chatlist_item_title, "chatlist_item_title");
    gtk_widget_set_halign(GTK_WIDGET(chatlist_item_title), GTK_ALIGN_START);
    gtk_widget_set_valign(GTK_WIDGET(chatlist_item_text), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(chatlist_item_text), chatlist_item_title, false, false, 0);

    // Initialize variables for message, time, and notification labels
    GtkWidget *chatlist_item_message = NULL;
    GtkWidget *chatlist_item_time = NULL;
    GtkWidget *chatlist_item_notify = NULL;

    // Retrieve the chat information and update the message, time, and notification labels
    t_chat *curr_chat = mx_get_chat_by_name(utils->chatlist, chat_name);
    if (curr_chat && curr_chat->last_new_msg)
    {
        char *msg_str = ellipsis_str(curr_chat->last_new_msg->text, 16);
        chatlist_item_message = gtk_label_new(msg_str);
        mx_strdel(&msg_str);
        chatlist_item_time = gtk_label_new(curr_chat->last_new_msg->date_str);
        chatlist_item_notify = gtk_label_new(mx_itoa(curr_chat->new_msg_count));
        // Show or hide notification count based on new message count
        curr_chat->new_msg_count > 0 ? add_class(chatlist_item_notify, "chatlist_item_notify--visible") : remove_class(chatlist_item_notify, "chatlist_item_notify--visible");
    }
    else if (!curr_chat->last_new_msg)
    {
        chatlist_item_message = gtk_label_new("No messages yet");
        chatlist_item_time = gtk_label_new("");
        chatlist_item_notify = gtk_label_new("");
    }

    // Pack message, time, and notification labels into the text block
    gtk_widget_set_halign(GTK_WIDGET(chatlist_item_message), GTK_ALIGN_START);
    gtk_widget_set_valign(GTK_WIDGET(chatlist_item_text), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(chatlist_item_text), chatlist_item_message, false, false, 0);
    gtk_widget_set_name(chatlist_item_message, "chatlist_item_message");
    add_class(chatlist_item_message, "chatlist_item_message");

    // Create a vertical box for the info block
    GtkWidget *chatlist_item_info = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(GTK_WIDGET(chatlist_item_info), GTK_ALIGN_END);
    // gtk_widget_set_valign(GTK_WIDGET(chatlist_item_info), GTK_ALIGN_END);
    gtk_box_pack_end(GTK_BOX(chatlist_item), chatlist_item_info, false, false, 0);
    add_class(chatlist_item_info, "chatlist_item_info");

    // Pack time and notification labels into the info block
    gtk_widget_set_valign(GTK_WIDGET(chatlist_item_time), GTK_ALIGN_START);
    gtk_widget_set_halign(GTK_WIDGET(chatlist_item_time), GTK_ALIGN_END);
    gtk_box_pack_start(GTK_BOX(chatlist_item_info), chatlist_item_time, false, false, 0);
    gtk_widget_set_name(chatlist_item_time, "chatlist_item_time");
    add_class(chatlist_item_time, "chatlist_item_time");

    gtk_widget_set_size_request(GTK_WIDGET(chatlist_item_notify), 20, 20);
    gtk_widget_set_valign(GTK_WIDGET(chatlist_item_notify), GTK_ALIGN_END);
    gtk_widget_set_halign(GTK_WIDGET(chatlist_item_notify), GTK_ALIGN_END);
    gtk_box_pack_start(GTK_BOX(chatlist_item_info), chatlist_item_notify, false, false, 0);
    gtk_widget_set_name(chatlist_item_notify, "chatlist_item_notify");
    add_class(chatlist_item_notify, "chatlist_item_notify");

    // Show the event box containing the chat list item
    gtk_widget_show_all(event_box);
}
