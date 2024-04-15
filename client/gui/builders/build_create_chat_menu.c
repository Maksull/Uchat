#include "../../inc/client.h"

// Function to create a vertical box for the chat creation menu elements
GtkWidget* create_chat_menu_box() {
    GtkWidget *create_chat_menu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    add_class(create_chat_menu, "popup_menu");
    return create_chat_menu;
}

// Function to create a label for the menu title
GtkWidget* create_menu_title_label() {
    GtkWidget *menu_title = gtk_label_new("Create new chat");
    gtk_widget_set_halign(GTK_WIDGET(menu_title), GTK_ALIGN_CENTER);
    add_class(menu_title, "popup_window_title");
    return menu_title;
}

// Function to create a label for the chat name input field
GtkWidget* create_chat_name_label() {
    GtkWidget *chat_name_label = gtk_label_new("Chat name:");
    gtk_widget_set_halign(GTK_WIDGET(chat_name_label), GTK_ALIGN_START);
    add_class(chat_name_label, "input-field_title");
    return chat_name_label;
}

// Function to create an entry field for the chat name
GtkWidget* create_chat_name_entry() {
    GtkWidget *chat_name_field = gtk_entry_new();
    gtk_widget_set_name(chat_name_field, "chat_name_field");
    gtk_entry_set_placeholder_text(GTK_ENTRY(chat_name_field), "Chat name");
    add_class(chat_name_field, "input-field");
    add_class(chat_name_field, "input-field--name");
    return chat_name_field;
}

// Function to create a label for notification related to chat name input
GtkWidget* create_chat_name_notify_label() {
    GtkWidget *chat_name_notify_label = gtk_label_new(" ");
    gtk_widget_set_halign(chat_name_notify_label, GTK_ALIGN_START);
    gtk_widget_set_name(chat_name_notify_label, "chat_name_notify_label");
    add_class(chat_name_notify_label, "notify-label");
    return chat_name_notify_label;
}

// Function to create a horizontal box for buttons
GtkWidget* create_button_box() {
    GtkWidget *btn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_halign(GTK_WIDGET(btn_box), GTK_ALIGN_CENTER);
    add_class(btn_box, "popup_btn_box");
    return btn_box;
}

// Function to create a button
GtkWidget* create_button(const char *label, bool blue) {
    GtkWidget *button = gtk_button_new_with_label(label);
    gtk_widget_set_size_request(GTK_WIDGET(button), 150, 50);
    g_signal_connect(G_OBJECT(button), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(button), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    if (blue)
        add_class(button, "btn--blue");
    else
        add_class(button, "btn--dark-blue");
    return button;
}

// Function to create and build chat menu
void build_create_chat_menu()
{
    GtkWidget *popup_window = create_popup_window(450, 0); // Create a popup window with specified width

    // Create a vertical box to contain the chat creation menu elements
    GtkWidget *create_chat_menu = create_chat_menu_box();
    gtk_container_add(GTK_CONTAINER(popup_window), create_chat_menu);

    // Create a label for the menu title
    GtkWidget *menu_title = create_menu_title_label();

    // Create a label for the chat name input field
    GtkWidget *chat_name_label = create_chat_name_label();

    // Create an entry field for the chat name
    GtkWidget *chat_name_field = create_chat_name_entry();
    // Create a label for notification related to chat name input
    GtkWidget *chat_name_notify_label = create_chat_name_notify_label();
    // Create a horizontal box for buttons
    GtkWidget *btn_box = create_button_box();
    // Create a button for creating a chat
    GtkWidget *create_chat_btn = create_button("Create", TRUE);
    // Create a button for canceling chat creation
    GtkWidget *cancel_btn = create_button("Cancel", FALSE);

    // Pack buttons into the button box
    gtk_box_pack_end(GTK_BOX(btn_box), create_chat_btn, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(btn_box), cancel_btn, FALSE, FALSE, 0);

    // Pack menu elements into the menu box
    gtk_box_pack_start(GTK_BOX(create_chat_menu), menu_title, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(create_chat_menu), chat_name_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(create_chat_menu), chat_name_field, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(create_chat_menu), chat_name_notify_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(create_chat_menu), btn_box, FALSE, FALSE, 0);

    // Show the popup window and grab focus to it
    gtk_widget_show_all(popup_window);
    gtk_widget_grab_focus(popup_window);
}
