#include "../../inc/client.h"

// Function to create a title label for the confirm leave chat window
static GtkWidget *create_confirm_leave_chat_title()
{
    GtkWidget *confirm_leave_chat_title = gtk_label_new("Leave chat");
    gtk_widget_set_halign(GTK_WIDGET(confirm_leave_chat_title), GTK_ALIGN_CENTER);
    add_class(confirm_leave_chat_title, "popup_window_title");
    
    return confirm_leave_chat_title;
}

// Function to create a label with the confirmation message
static GtkWidget *create_confirm_leave_chat_label()
{
    GtkWidget *confirm_leave_chat_label = gtk_label_new("Are you sure you want to leave chat?");
    gtk_widget_set_halign(GTK_WIDGET(confirm_leave_chat_label), GTK_ALIGN_CENTER);
    add_class(confirm_leave_chat_label, "confirm_text");

    return confirm_leave_chat_label;
}

// Function to create a horizontal box to hold the buttons
static GtkWidget *create_confirm_leave_chat_btn_box()
{
    GtkWidget *btn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_halign(GTK_WIDGET(btn_box), GTK_ALIGN_CENTER);
    add_class(btn_box, "popup_btn_box");

    return btn_box;
}

// Function to create the "Leave" button for confirming leaving the chat
static GtkWidget *create_confirm_leave_chat_btn()
{
    GtkWidget *confirm_leave_chat_btn = gtk_button_new_with_label("Leave");
    gtk_widget_set_size_request(GTK_WIDGET(confirm_leave_chat_btn), 150, 50);
    g_signal_connect(G_OBJECT(confirm_leave_chat_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(confirm_leave_chat_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(confirm_leave_chat_btn), "clicked", G_CALLBACK(leave_chat_btn_click), NULL);
    add_class(confirm_leave_chat_btn, "btn");
    add_class(confirm_leave_chat_btn, "btn--blue");

    return confirm_leave_chat_btn;
}

// Function to create the "Cancel" button
static GtkWidget *create_cancel_btn()
{
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
static void pack_buttons_into_btn_box(GtkWidget *btn_box, GtkWidget *confirm_leave_chat_btn, GtkWidget *cancel_btn)
{
    gtk_box_pack_end(GTK_BOX(btn_box), confirm_leave_chat_btn, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(btn_box), cancel_btn, FALSE, FALSE, 0);
}

// Function to pack elements into the confirmation box
static void pack_elements_into_confirm_leave_chat_box(GtkWidget *confirm_leave_chat_box, GtkWidget *confirm_leave_chat_title, GtkWidget *confirm_leave_chat_label, GtkWidget *btn_box)
{
    gtk_box_pack_start(GTK_BOX(confirm_leave_chat_box), confirm_leave_chat_title, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(confirm_leave_chat_box), confirm_leave_chat_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(confirm_leave_chat_box), btn_box, FALSE, FALSE, 0);
}

// Function to build confirm leave chat window
void build_confirm_leave_chat_window(GtkWidget *widget, gpointer data)
{
    if (widget)
    { }
    (void)data;

    GtkWidget *popup_window = create_popup_window(400, 0);                        // Create a popup window
    GtkWidget *confirm_leave_chat_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); // Create a vertical box to hold the confirmation elements

    gtk_container_add(GTK_CONTAINER(popup_window), confirm_leave_chat_box); // Add the confirmation box to the popup window
    // Add CSS classes to style the confirmation box
    add_class(confirm_leave_chat_box, "popup_menu");
    add_class(confirm_leave_chat_box, "edit_profile_menu");

    // Create a title label for the confirmation window
    GtkWidget *confirm_leave_chat_title = create_confirm_leave_chat_title();

    // Create a label with the confirmation message
    GtkWidget *confirm_leave_chat_label = create_confirm_leave_chat_label();

    // Create a horizontal box to hold the buttons
    GtkWidget *btn_box = create_confirm_leave_chat_btn_box();

    // Create a button to confirm leaving the chat
    GtkWidget *confirm_leave_chat_btn = create_confirm_leave_chat_btn();

    // Create a button to cancel leaving the chat
    GtkWidget *cancel_btn = create_cancel_btn();

    // Pack the buttons into the button box
    pack_buttons_into_btn_box(btn_box, confirm_leave_chat_btn, cancel_btn);

    // Pack the title, confirmation message, and button box into the confirmation box
    pack_elements_into_confirm_leave_chat_box(confirm_leave_chat_box, confirm_leave_chat_title, confirm_leave_chat_label, btn_box);

    gtk_widget_show_all(popup_window);   // Show all widgets in the popup window
    gtk_widget_grab_focus(popup_window); // Set focus to the popup window
}
