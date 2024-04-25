#include "../../inc/client.h"

// Function to create the title label for the confirmation window
static GtkWidget *create_confirm_logout_title()
{
    GtkWidget *confirm_logout_title = gtk_label_new("Log out");
    gtk_widget_set_halign(GTK_WIDGET(confirm_logout_title), GTK_ALIGN_CENTER);
    add_class(confirm_logout_title, "popup_window_title");
    
    return confirm_logout_title;
}

// Function to create the message label for confirming logout
static GtkWidget *create_confirm_logout_message()
{
    GtkWidget *confirm_logout_label = gtk_label_new("Are you sure you want to log out?");
    gtk_widget_set_halign(GTK_WIDGET(confirm_logout_label), GTK_ALIGN_CENTER);
    add_class(confirm_logout_label, "confirm_text");

    return confirm_logout_label;
}

// Function to create a horizontal box for buttons
static GtkWidget *create_horizontal_button_box()
{
    GtkWidget *btn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_halign(GTK_WIDGET(btn_box), GTK_ALIGN_CENTER);
    add_class(btn_box, "popup_btn_box");

    return btn_box;
}

// Function to create the "Log out" button
static GtkWidget *create_logout_button()
{
    GtkWidget *confirm_logout_btn = gtk_button_new_with_label("Log out");
    gtk_widget_set_size_request(GTK_WIDGET(confirm_logout_btn), 150, 50);
    g_signal_connect(G_OBJECT(confirm_logout_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(confirm_logout_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(confirm_logout_btn), "clicked", G_CALLBACK(logout_btn_click), NULL);
    add_class(confirm_logout_btn, "btn");
    add_class(confirm_logout_btn, "btn--blue");

    return confirm_logout_btn;
}

// Function to create the "Cancel" button
static GtkWidget *create_cancel_button()
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

// Function to pack buttons into a box
static void pack_buttons_into_box(GtkWidget *btn_box, GtkWidget *button1, GtkWidget *button2)
{
    gtk_box_pack_end(GTK_BOX(btn_box), button1, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(btn_box), button2, FALSE, FALSE, 0);
}

// Function to pack elements into the confirmation box
static void pack_elements_into_confirmation_box(GtkWidget *confirm_logout_box, GtkWidget *title, GtkWidget *message, GtkWidget *btn_box)
{
    gtk_box_pack_start(GTK_BOX(confirm_logout_box), title, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(confirm_logout_box), message, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(confirm_logout_box), btn_box, FALSE, FALSE, 0);
}

// Function to build confirm logout window
void build_confirm_logout_window(GtkWidget *widget, gpointer data)
{
    if (widget)
    { }
    (void)data;

    GtkWidget *popup_window = create_popup_window(400, 0);                    // Create a popup window
    GtkWidget *confirm_logout_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); // Create a vertical box for the confirmation window

    gtk_container_add(GTK_CONTAINER(popup_window), confirm_logout_box); // Add the confirmation box to the popup window
    // Add CSS classes to style the confirmation box
    add_class(confirm_logout_box, "popup_menu");
    add_class(confirm_logout_box, "edit_profile_menu");

    // Create the title label for the confirmation window
    GtkWidget *confirm_logout_title = create_confirm_logout_title();

    // Create the message label for confirming logout
    GtkWidget *confirm_logout_label = create_confirm_logout_message();

    // Create a horizontal box for buttons
    GtkWidget *btn_box = create_horizontal_button_box();

    // Create the "Log out" button
    GtkWidget *confirm_logout_btn = create_logout_button();

    // Create the "Cancel" button
    GtkWidget *cancel_btn = create_cancel_button();

    // Add buttons to the button box
    pack_buttons_into_box(btn_box, confirm_logout_btn, cancel_btn);

    // Pack elements into the confirmation box
    pack_elements_into_confirmation_box(confirm_logout_box, confirm_logout_title, confirm_logout_label, btn_box);

    // Show all elements in the popup window and set focus to it
    gtk_widget_show_all(popup_window);
    gtk_widget_grab_focus(popup_window);
}
