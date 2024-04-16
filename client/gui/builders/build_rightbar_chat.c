#include "../../inc/client.h"

// Function to create the chat header
static GtkWidget *create_chat_header()
{
    GtkWidget *chat_header = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_widget_set_hexpand(chat_header, TRUE);
    add_class(chat_header, "chat_header");
    return chat_header;
}

// Function to create and configure the avatar widget
static GtkWidget *create_avatar_widget()
{
    GtkWidget *avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 42, 42);
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_chat_avatar), (gpointer)utils->current_chat->avatar_color);
    gtk_widget_set_halign(avatar, GTK_ALIGN_START);
    gtk_widget_set_valign(avatar, GTK_ALIGN_CENTER);
    return avatar;
}

// Function to create and configure the chat header title widget
static GtkWidget *create_chat_header_title()
{
    GtkWidget *chat_header_title = gtk_label_new(utils->current_chat->name);
    gtk_widget_set_name(chat_header_title, "chat_header_title");
    gtk_widget_set_halign(GTK_WIDGET(chat_header_title), GTK_ALIGN_START);
    gtk_widget_set_valign(GTK_WIDGET(chat_header_title), GTK_ALIGN_CENTER);
    add_class(chat_header_title, "chat_title");
    return chat_header_title;
}

// Function to add additional buttons based on user permissions in the chat
static void add_permission_buttons(GtkWidget *chat_header)
{
    if (utils->current_chat->permissions == ADMIN_MEMBER)
    {
        // Delete chat button
        GtkWidget *delete_chat_btn = gtk_event_box_new();
        add_class(delete_chat_btn, "event_switch_auth_menu");
        gtk_widget_set_halign(GTK_WIDGET(delete_chat_btn), GTK_ALIGN_CENTER);
        g_signal_connect(G_OBJECT(delete_chat_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
        g_signal_connect(G_OBJECT(delete_chat_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
        g_signal_connect(G_OBJECT(delete_chat_btn), "button_press_event", G_CALLBACK(build_confirm_delete_chat_window), NULL);
        GtkWidget *delete_chat_label = gtk_label_new("Delete chat");
        add_class(delete_chat_label, "switch_auth_menu_label");
        gtk_container_add(GTK_CONTAINER(delete_chat_btn), delete_chat_label);
        gtk_box_pack_end(GTK_BOX(chat_header), delete_chat_btn, FALSE, FALSE, 0);

        // Change chat name button
        GtkWidget *change_chat_name_btn = gtk_event_box_new();
        add_class(change_chat_name_btn, "event_switch_auth_menu");
        gtk_widget_set_halign(GTK_WIDGET(change_chat_name_btn), GTK_ALIGN_CENTER);
        g_signal_connect(G_OBJECT(change_chat_name_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
        g_signal_connect(G_OBJECT(change_chat_name_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
        g_signal_connect(G_OBJECT(change_chat_name_btn), "button_press_event", G_CALLBACK(build_change_chat_name_window), NULL);
        GtkWidget *change_chat_name_label = gtk_label_new("Change chat name");
        add_class(change_chat_name_label, "switch_auth_menu_label");
        gtk_container_add(GTK_CONTAINER(change_chat_name_btn), change_chat_name_label);
        gtk_box_pack_end(GTK_BOX(chat_header), change_chat_name_btn, FALSE, FALSE, 0);
    }
    else
    {
        // Leave chat button
        GtkWidget *leave_chat_btn = gtk_event_box_new();
        add_class(leave_chat_btn, "event_switch_auth_menu");
        gtk_widget_set_halign(GTK_WIDGET(leave_chat_btn), GTK_ALIGN_CENTER);
        g_signal_connect(G_OBJECT(leave_chat_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
        g_signal_connect(G_OBJECT(leave_chat_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
        g_signal_connect(G_OBJECT(leave_chat_btn), "button_press_event", G_CALLBACK(build_confirm_leave_chat_window), NULL);
        GtkWidget *leave_chat_label = gtk_label_new("Leave chat");
        add_class(leave_chat_label, "switch_auth_menu_label");
        gtk_container_add(GTK_CONTAINER(leave_chat_btn), leave_chat_label);
        gtk_box_pack_end(GTK_BOX(chat_header), leave_chat_btn, FALSE, FALSE, 0);
    }
}

// Function to create the scrollable wrap for messages
static GtkWidget *create_scrollable_wrap()
{
    GtkWidget *scrollable_wrap = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_name(scrollable_wrap, "scrollable_wrap");
    return scrollable_wrap;
}

// Function to create the chat field for messages
static GtkWidget *create_chat_field()
{
    GtkWidget *chat_field = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(chat_field, "chat_field");
    gtk_widget_set_hexpand(chat_field, TRUE);
    add_class(chat_field, "messagelist");
    gtk_widget_set_events(chat_field, GDK_ALL_EVENTS_MASK);
    g_signal_connect(chat_field, "size-allocate", G_CALLBACK(scroll_to_end), NULL);
    return chat_field;
}

// Function to create the message field for typing new messages
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

// Function to create and configure the new message entry field
static GtkWidget *create_new_message_entry_field()
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

// Function to create and configure the send button
static GtkWidget *create_send_button(GtkWidget *new_message_field)
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
    GtkWidget *chat_container = get_widget_by_name_r(main_window, "chat");
    gtk_container_foreach(GTK_CONTAINER(chat_container), (GtkCallback)gtk_widget_destroy, NULL);

    GtkWidget *chat_header = create_chat_header();
    create_avatar_widget();
    create_chat_header_title();
    add_permission_buttons(chat_header);

    GtkWidget *scrollable_wrap = create_scrollable_wrap();
    GtkWidget *chat_field = create_chat_field();
    gtk_container_add(GTK_CONTAINER(scrollable_wrap), chat_field);
    GtkWidget *message_field = create_message_field();
    GtkWidget *new_message_field = create_new_message_entry_field();
    GtkWidget *send_btn = create_send_button(new_message_field);

    gtk_box_pack_start(GTK_BOX(chat_container), chat_header, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(chat_container), scrollable_wrap, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(message_field), send_btn, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(chat_container), message_field, FALSE, FALSE, 0);

    update_chat_field();
    gtk_widget_show_all(chat_container);
}
