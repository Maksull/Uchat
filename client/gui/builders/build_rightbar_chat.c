#include "../../inc/client.h"

// Helper for creating avatar widget
static GtkWidget *create_avatar()
{
    GtkWidget *avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 42, 42);
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_chat_avatar), (gpointer)utils->current_chat->avatar_color);
    gtk_widget_set_halign(avatar, GTK_ALIGN_START);
    gtk_widget_set_valign(avatar, GTK_ALIGN_CENTER);

    return avatar;
}

// Helper for creating chat handler title widget
static GtkWidget *create_chat_header_title()
{
    GtkWidget *chat_header_title = gtk_label_new(utils->current_chat->name);
    gtk_widget_set_name(chat_header_title, "chat_header_title");
    gtk_widget_set_halign(GTK_WIDGET(chat_header_title), GTK_ALIGN_START);
    gtk_widget_set_valign(GTK_WIDGET(chat_header_title), GTK_ALIGN_CENTER);
    add_class(chat_header_title, "chat_title");

    return chat_header_title;
}

// Helper for creating delete chat btn widget
static GtkWidget *create_delete_chat_btn()
{
    GtkWidget *delete_chat_btn = gtk_event_box_new();
    add_class(delete_chat_btn, "event_switch_auth_menu");
    gtk_widget_set_halign(GTK_WIDGET(delete_chat_btn), GTK_ALIGN_CENTER);
    g_signal_connect(G_OBJECT(delete_chat_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(delete_chat_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(delete_chat_btn), "button_press_event", G_CALLBACK(build_confirm_delete_chat_window), NULL);

    return delete_chat_btn;
}

// Helper for creating change chat name btn widget
static GtkWidget *create_change_chat_name_btn()
{
    GtkWidget *change_chat_name_btn = gtk_event_box_new();
    add_class(change_chat_name_btn, "event_switch_auth_menu");
    gtk_widget_set_halign(GTK_WIDGET(change_chat_name_btn), GTK_ALIGN_CENTER);
    g_signal_connect(G_OBJECT(change_chat_name_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(change_chat_name_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(change_chat_name_btn), "button_press_event", G_CALLBACK(build_change_chat_name_window), NULL);

    return change_chat_name_btn;
}

// Helper for creating leave chat btn widget
static GtkWidget *create_leave_chat_btn()
{
    GtkWidget *leave_chat_btn = gtk_event_box_new();
    add_class(leave_chat_btn, "event_switch_auth_menu");
    gtk_widget_set_halign(GTK_WIDGET(leave_chat_btn), GTK_ALIGN_CENTER);
    g_signal_connect(G_OBJECT(leave_chat_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(leave_chat_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(leave_chat_btn), "button_press_event", G_CALLBACK(build_confirm_leave_chat_window), NULL);

    return leave_chat_btn;
}

// Helper for creating message field widget
static GtkWidget *create_message_field()
{
    GtkWidget *message_field = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(message_field, "message_field");
    add_class(message_field, "input-msg_box");
    gtk_widget_set_halign(GTK_WIDGET(message_field), GTK_ALIGN_FILL);
    gtk_widget_set_valign(GTK_WIDGET(message_field), GTK_ALIGN_FILL);

    gtk_widget_set_hexpand(message_field, TRUE);
    return message_field;
}

// Helper for creating new message field widget
static GtkWidget *create_new_message_field()
{
    GtkWidget *new_message_field = gtk_entry_new();
    gtk_widget_set_name(new_message_field, "new_message_field");
    add_class(new_message_field, "input-msg_entry");
    gtk_entry_set_placeholder_text(GTK_ENTRY(new_message_field), "Message");
    gtk_widget_set_halign(GTK_WIDGET(new_message_field), GTK_ALIGN_FILL);
    gtk_widget_set_valign(GTK_WIDGET(new_message_field), GTK_ALIGN_FILL);
    gtk_entry_set_max_length(GTK_ENTRY(new_message_field), 100);
    g_signal_connect(new_message_field, "activate", G_CALLBACK(send_button_click), new_message_field);

    return new_message_field;
}

// Helper for creating send btn widget
static GtkWidget *create_send_btn(GtkWidget *new_message_field)
{
    GtkWidget *send_btn = gtk_button_new();
    gtk_widget_set_size_request(GTK_WIDGET(send_btn), 55, 55);
    gtk_widget_set_name(send_btn, "send_btn");
    add_class(send_btn, "input-msg_send-btn");
    g_signal_connect(G_OBJECT(send_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(send_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(send_btn, "clicked", G_CALLBACK(send_button_click), new_message_field);
    gtk_widget_set_halign(GTK_WIDGET(send_btn), GTK_ALIGN_END);
    gtk_widget_set_valign(GTK_WIDGET(send_btn), GTK_ALIGN_END);

    return send_btn;
}

// Function to build rightbar chat
void build_rightbar_chat()
{
    GtkWidget *chat_container = get_widget_by_name_r(main_window, "chat"); // Get the chat container

    gtk_container_foreach(GTK_CONTAINER(chat_container), (GtkCallback)gtk_widget_destroy, NULL); // Remove existing widgets in the chat container

    // Create the chat header
    GtkWidget *chat_header = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_widget_set_hexpand(chat_header, TRUE);
    add_class(chat_header, "chat_header");

    // Create and configure the avatar widget
    GtkWidget *avatar = create_avatar();
    gtk_box_pack_start(GTK_BOX(chat_header), avatar, FALSE, FALSE, 0);

    // Create and configure the chat header title widget
    GtkWidget *chat_header_title = create_chat_header_title();
    gtk_box_pack_start(GTK_BOX(chat_header), chat_header_title, FALSE, FALSE, 0);

    // Add additional buttons based on user permissions in the chat
    if (utils->current_chat->permissions == ADMIN_MEMBER)
    {
        // Delete chat button
        GtkWidget *delete_chat_btn = create_delete_chat_btn();
        GtkWidget *delete_chat_label = gtk_label_new("Delete chat");
        add_class(delete_chat_label, "switch_auth_menu_label");
        gtk_container_add(GTK_CONTAINER(delete_chat_btn), delete_chat_label);
        gtk_box_pack_end(GTK_BOX(chat_header), delete_chat_btn, FALSE, FALSE, 0);

        // Change chat name button
        GtkWidget *change_chat_name_btn = create_change_chat_name_btn();
        GtkWidget *change_chat_name_label = gtk_label_new("Change chat name");
        add_class(change_chat_name_label, "switch_auth_menu_label");
        gtk_container_add(GTK_CONTAINER(change_chat_name_btn), change_chat_name_label);
        gtk_box_pack_end(GTK_BOX(chat_header), change_chat_name_btn, FALSE, FALSE, 0);
    }
    else
    {
        // Leave chat button
        GtkWidget *leave_chat_btn = create_leave_chat_btn();
        GtkWidget *leave_chat_label = gtk_label_new("Leave chat");
        add_class(leave_chat_label, "switch_auth_menu_label");
        gtk_container_add(GTK_CONTAINER(leave_chat_btn), leave_chat_label);
        gtk_box_pack_end(GTK_BOX(chat_header), leave_chat_btn, FALSE, FALSE, 0);
    }

    // Create the scrollable wrap for messages
    GtkWidget *scrollable_wrap = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_name(scrollable_wrap, "scrollable_wrap");

    // Create the chat field for messages
    GtkWidget *chat_field = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(chat_field, "chat_field");
    gtk_widget_set_hexpand(chat_field, TRUE);
    add_class(chat_field, "messagelist");
    gtk_widget_set_events(chat_field, GDK_ALL_EVENTS_MASK);
    g_signal_connect(chat_field, "size-allocate", G_CALLBACK(scroll_to_end), NULL);
    gtk_container_add(GTK_CONTAINER(scrollable_wrap), chat_field);

    // Create the message field for typing new messages
    GtkWidget *message_field = create_message_field();
    gtk_box_pack_end(GTK_BOX(chat_container), message_field, false, false, 0);

    // Create the new message entry field
    GtkWidget *new_message_field = create_new_message_field();
    gtk_box_pack_start(GTK_BOX(message_field), new_message_field, TRUE, TRUE, 0);

    // Create and configure the send button
    GtkWidget *send_btn = create_send_btn(new_message_field);

    // Pack the widgets into the chat container
    gtk_box_pack_start(GTK_BOX(chat_container), chat_header, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(chat_container), scrollable_wrap, true, true, 0);
    gtk_box_pack_start(GTK_BOX(message_field), send_btn, FALSE, FALSE, 0);

    // Update the chat field with messages
    update_chat_field();

    // Show all widgets in the chat container
    gtk_widget_show_all(chat_container);
}
