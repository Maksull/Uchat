#include "../../inc/client.h"

// Function to create the title label for confirm delete chat window
static GtkWidget *create_confirm_delete_chat_title()
{
    // Create the title label
    GtkWidget *confirm_delete_chat_title = gtk_label_new("Delete chat");
    gtk_widget_set_halign(GTK_WIDGET(confirm_delete_chat_title), GTK_ALIGN_CENTER);
    add_class(confirm_delete_chat_title, "popup_window_title");

    return confirm_delete_chat_title;
}

// Function to create the confirmation message label for confirm delete chat window
static GtkWidget *create_confirm_delete_chat_label()
{
    // Create the confirmation message label
    GtkWidget *confirm_delete_chat_label = gtk_label_new("Are you sure you want to delete chat?");
    gtk_widget_set_halign(GTK_WIDGET(confirm_delete_chat_label), GTK_ALIGN_CENTER);
    add_class(confirm_delete_chat_label, "confirm_text");

    return confirm_delete_chat_label;
}

// Function to create the button box for confirm and cancel buttons
static GtkWidget *create_confirm_delete_chat_button_box()
{
    // Create the button box
    GtkWidget *btn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_halign(GTK_WIDGET(btn_box), GTK_ALIGN_CENTER);
    add_class(btn_box, "popup_btn_box");

    return btn_box;
}

// Function to create the delete button for the confirm delete chat window
static GtkWidget *create_confirm_delete_chat_button()
{
    // Create the delete button
    GtkWidget *confirm_delete_chat_btn = gtk_button_new_with_label("Delete");
    gtk_widget_set_size_request(GTK_WIDGET(confirm_delete_chat_btn), 150, 50);
    g_signal_connect(G_OBJECT(confirm_delete_chat_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(confirm_delete_chat_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(confirm_delete_chat_btn), "clicked", G_CALLBACK(delete_chat_btn_click), NULL);
    add_class(confirm_delete_chat_btn, "btn");
    add_class(confirm_delete_chat_btn, "btn--blue");

    return confirm_delete_chat_btn;
}

// Function to create the cancel button for the confirm delete chat window
static GtkWidget *create_confirm_delete_cancel_button()
{
    // Create the cancel button
    GtkWidget *cancel_btn = gtk_button_new_with_label("Cancel");
    gtk_widget_set_size_request(GTK_WIDGET(cancel_btn), 150, 50);
    g_signal_connect(G_OBJECT(cancel_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(cancel_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(cancel_btn), "clicked", G_CALLBACK(destroy_popup_window), NULL);
    add_class(cancel_btn, "btn");
    add_class(cancel_btn, "btn--dark-blue");

    return cancel_btn;
}

// Function to pack buttons into the button box
static void pack_buttons_into_button_box(GtkWidget *btn_box, GtkWidget *confirm_btn, GtkWidget *cancel_btn)
{
    gtk_box_pack_end(GTK_BOX(btn_box), confirm_btn, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(btn_box), cancel_btn, FALSE, FALSE, 0);
}

// Function to pack widgets into the confirm delete chat box
static void pack_widgets_into_confirm_delete_chat_box(GtkWidget *confirm_delete_chat_box, GtkWidget *confirm_delete_chat_title, GtkWidget *confirm_delete_chat_label, GtkWidget *btn_box)
{
    gtk_box_pack_start(GTK_BOX(confirm_delete_chat_box), confirm_delete_chat_title, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(confirm_delete_chat_box), confirm_delete_chat_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(confirm_delete_chat_box), btn_box, FALSE, FALSE, 0);
}

// Function to build confirm delete chat window
void build_confirm_delete_chat_window(GtkWidget *widget, gpointer data)
{
    if (widget)
    { }
    (void)data;

    // Create the popup window
    GtkWidget *popup_window = create_popup_window(400, 0);
    GtkWidget *confirm_delete_chat_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    // Add the popup box to the window
    gtk_container_add(GTK_CONTAINER(popup_window), confirm_delete_chat_box);
    add_class(confirm_delete_chat_box, "popup_menu");
    add_class(confirm_delete_chat_box, "edit_profile_menu");

    // Create the title label
    GtkWidget *confirm_delete_chat_title = create_confirm_delete_chat_title();
    // Create the confirmation message label
    GtkWidget *confirm_delete_chat_label = create_confirm_delete_chat_label();

    // Button box for confirm and cancel buttons
    GtkWidget *btn_box = create_confirm_delete_chat_button_box();

    // Create the delete button
    GtkWidget *confirm_delete_chat_btn = create_confirm_delete_chat_button();

    // Create the cancel button
    GtkWidget *cancel_btn = create_confirm_delete_cancel_button();

    // Pack buttons into the button box
    pack_buttons_into_button_box(btn_box, confirm_delete_chat_btn, cancel_btn);

    // Pack widgets into the popup box
    pack_widgets_into_confirm_delete_chat_box(confirm_delete_chat_box, confirm_delete_chat_title, confirm_delete_chat_label, btn_box);

    // Show all widgets and grab focus on the popup window
    gtk_widget_show_all(popup_window);
    gtk_widget_grab_focus(popup_window);
}
