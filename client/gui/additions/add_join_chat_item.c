#include "../../inc/client.h"

// Function to handle add join chat item
void add_join_chat_item(int id, char *chat_name, t_avatar_color avatar_color)
{
    GtkWidget *chatlist_container = get_widget_by_name_r(main_window, "chatlist"); // Get the chat list container widget

    // Create an event box for the chat item
    GtkWidget *event_box = gtk_event_box_new();
    gtk_event_box_set_above_child(GTK_EVENT_BOX(event_box), TRUE);
    gtk_box_pack_start(GTK_BOX(chatlist_container), event_box, FALSE, FALSE, 0);
    gtk_widget_set_name(event_box, chat_name);
    add_class(event_box, "chatlist_item_wrap");

    // Connect event handlers for mouse events
    g_signal_connect(G_OBJECT(event_box), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(event_box), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(event_box), "button_press_event", G_CALLBACK(join_chat_event), NULL);

    // Create the chat item box
    GtkWidget *chatlist_item = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(chatlist_item, mx_itoa(id));
    add_class(chatlist_item, "chatlist_item");
    gtk_container_add(GTK_CONTAINER(event_box), chatlist_item);

    // Add the chat ID as a hidden label
    GtkWidget *chatlist_item_id = gtk_label_new(mx_itoa(id)); ///CHAT ID
    gtk_widget_set_name(chatlist_item_id, "chat_id");
    add_class(chatlist_item_id, "hidden");
    gtk_box_pack_start(GTK_BOX(chatlist_item), chatlist_item_id, FALSE, FALSE, 0);

    // Create and add the avatar drawing area
    GtkWidget *avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 42, 42);
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_chat_avatar), (gpointer)avatar_color);
    gtk_widget_set_halign(avatar, GTK_ALIGN_START);
    gtk_widget_set_valign(avatar, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(chatlist_item), avatar, FALSE, FALSE, 0);

    // Create the text block for chat item details
    GtkWidget *chatlist_item_text = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(GTK_WIDGET(chatlist_item_text), GTK_ALIGN_START);
    gtk_widget_set_valign(GTK_WIDGET(chatlist_item_text), GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(chatlist_item), chatlist_item_text, false, false, 0);
    add_class(chatlist_item_text, "chatlist_item_text");

    // Add the chat name as a label to the text block
    GtkWidget *chatlist_item_title = gtk_label_new(chat_name);
    add_class(chatlist_item_title, "chatlist_item_title");
    gtk_widget_set_halign(GTK_WIDGET(chatlist_item_title), GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(chatlist_item_text), chatlist_item_title, false, false, 0);

    gtk_widget_show_all(event_box); // Show all widgets within the event box
}
