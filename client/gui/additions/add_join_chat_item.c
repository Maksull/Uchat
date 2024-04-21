#include "../../inc/client.h"

// Helper function to create a drawing area for the chat avatar
static GtkWidget *create_avatar_drawing_area(t_avatar_color avatar_color)
{
    GtkWidget *avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 42, 42);
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_chat_avatar), (gpointer)avatar_color);
    gtk_widget_set_halign(avatar, GTK_ALIGN_START);
    gtk_widget_set_valign(avatar, GTK_ALIGN_CENTER);
    
    return avatar;
}

// Helper function to create a vertical box widget
static GtkWidget *create_vertical_box()
{
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(GTK_WIDGET(box), GTK_ALIGN_START);
    gtk_widget_set_valign(GTK_WIDGET(box), GTK_ALIGN_START);

    return box;
}

// Function to create the event box for the chat item
static GtkWidget *create_chat_event_box(const char *chat_name, GtkWidget *chatlist_container)
{
    GtkWidget *event_box = gtk_event_box_new();
    gtk_event_box_set_above_child(GTK_EVENT_BOX(event_box), TRUE);
    gtk_box_pack_start(GTK_BOX(chatlist_container), event_box, FALSE, FALSE, 0);
    gtk_widget_set_name(event_box, chat_name);
    add_class(event_box, "chatlist_item_wrap");
    // Connect event handlers for mouse events
    g_signal_connect(G_OBJECT(event_box), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(event_box), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(event_box), "button_press_event", G_CALLBACK(join_chat_event), NULL);

    return event_box;
}

// Function to create the chat item box
static GtkWidget *create_chat_item_box(int id, GtkWidget *event_box)
{
    GtkWidget *chatlist_item = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_name(chatlist_item, mx_itoa(id));
    add_class(chatlist_item, "chatlist_item");
    gtk_container_add(GTK_CONTAINER(event_box), chatlist_item);

    return chatlist_item;
}

// Function to create and configure the hidden label for the chat ID
static GtkWidget *create_hidden_chat_id_label(int id, GtkWidget *chatlist_item)
{
    GtkWidget *chatlist_item_id = gtk_label_new(mx_itoa(id)); // CHAT ID
    gtk_widget_set_name(chatlist_item_id, "chat_id");
    add_class(chatlist_item_id, "hidden");
    gtk_box_pack_start(GTK_BOX(chatlist_item), chatlist_item_id, FALSE, FALSE, 0);

    return chatlist_item_id;
}

// Function to create and pack the avatar drawing area
static GtkWidget *create_and_pack_avatar(GtkWidget *chatlist_item, t_avatar_color avatar_color)
{
    GtkWidget *avatar = create_avatar_drawing_area(avatar_color);
    gtk_box_pack_start(GTK_BOX(chatlist_item), avatar, FALSE, FALSE, 0);

    return avatar;
}

// Function to create and pack the text block for chat item details
static GtkWidget *create_and_pack_text_block(GtkWidget *chatlist_item)
{
    GtkWidget *chatlist_item_text = create_vertical_box();
    gtk_box_pack_start(GTK_BOX(chatlist_item), chatlist_item_text, FALSE, FALSE, 0);
    add_class(chatlist_item_text, "chatlist_item_text");

    return chatlist_item_text;
}

// Function to create and pack the chat name label within the text block
static GtkWidget *create_and_pack_chat_name_label(const char *chat_name, GtkWidget *chatlist_item_text)
{
    GtkWidget *chatlist_item_title = gtk_label_new(chat_name);
    add_class(chatlist_item_title, "chatlist_item_title");
    gtk_widget_set_halign(GTK_WIDGET(chatlist_item_title), GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(chatlist_item_text), chatlist_item_title, FALSE, FALSE, 0);

    return chatlist_item_title;
}

// Function to handle add join chat item
void add_join_chat_item(int id, char *chat_name, t_avatar_color avatar_color)
{
    GtkWidget *chatlist_container = get_widget_by_name_r(main_window, "chatlist"); // Get the chat list container widget

    // Create an event box for the chat item
    GtkWidget *event_box = create_chat_event_box(chat_name, chatlist_container);

    // Create the chat item box
    GtkWidget *chatlist_item = create_chat_item_box(id, event_box);

    // Add the chat ID as a hidden label
    GtkWidget *chatlist_item_id = create_hidden_chat_id_label(id, chatlist_item);

    // Create and add the avatar drawing area
    GtkWidget *avatar = create_and_pack_avatar(chatlist_item, avatar_color);

    // Create the text block for chat item details
    GtkWidget *chatlist_item_text = create_and_pack_text_block(chatlist_item);

    // Add the chat name as a label to the text block
    GtkWidget *chatlist_item_title = create_and_pack_chat_name_label(chat_name, chatlist_item_text);

    gtk_widget_show_all(event_box); // Show all widgets within the event box
}
