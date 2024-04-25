#include "../../inc/client.h"

// Function definition to create the confirmation box for deleting account
static GtkWidget *create_confirm_delete_account_box(GtkWidget *popup_window)
{
    // Create a vertical box to hold the confirmation components
    GtkWidget *confirm_delete_account_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    // Add the confirmation box to the popup window
    gtk_container_add(GTK_CONTAINER(popup_window), confirm_delete_account_box);
    // Set CSS classes for styling
    add_class(confirm_delete_account_box, "popup_menu");
    add_class(confirm_delete_account_box, "edit_profile_menu");

    return confirm_delete_account_box;
}

// Function definition to create the title label for confirming account deletion
static GtkWidget *create_confirm_delete_account_title()
{
    // Create the title label
    GtkWidget *confirm_delete_account_title = gtk_label_new("Delete account");
    // Set horizontal alignment to center
    gtk_widget_set_halign(GTK_WIDGET(confirm_delete_account_title), GTK_ALIGN_CENTER);
    // Add CSS class for styling
    add_class(confirm_delete_account_title, "popup_window_title");

    return confirm_delete_account_title;
}

// Function definition to create the label for confirming account deletion
static GtkWidget *create_confirm_delete_account_label()
{
    // Create the label
    GtkWidget *confirm_delete_account_label = gtk_label_new("Are you sure you want to delete account?");
    // Set horizontal alignment to center
    gtk_widget_set_halign(GTK_WIDGET(confirm_delete_account_label), GTK_ALIGN_CENTER);
    // Add CSS class for styling
    add_class(confirm_delete_account_label, "confirm_text");

    return confirm_delete_account_label;
}

// Function definition to create the button box for confirming or canceling the account deletion
static GtkWidget *create_confirm_delete_account_btn_box()
{
    // Create the button box
    GtkWidget *btn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    // Set horizontal alignment to center
    gtk_widget_set_halign(GTK_WIDGET(btn_box), GTK_ALIGN_CENTER);
    // Add CSS class for styling
    add_class(btn_box, "popup_btn_box");

    return btn_box;
}

// Function definition to create the delete button
static GtkWidget *create_confirm_delete_account_btn()
{
    // Create the delete button
    GtkWidget *confirm_delete_account_btn = gtk_button_new_with_label("Delete");
    // Set the size of the button
    gtk_widget_set_size_request(GTK_WIDGET(confirm_delete_account_btn), 150, 50);
    // Connect signal handlers for mouse enter and leave events on the button
    g_signal_connect(G_OBJECT(confirm_delete_account_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(confirm_delete_account_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    // Connect a signal handler to the "clicked" signal of the button
    g_signal_connect(G_OBJECT(confirm_delete_account_btn), "clicked", G_CALLBACK(delete_account_btn_click), NULL);
    // Add CSS classes to the button for styling purposes
    add_class(confirm_delete_account_btn, "btn");
    add_class(confirm_delete_account_btn, "btn--blue");

    return confirm_delete_account_btn;
}

// Function definition to create the cancel button
static GtkWidget *create_cancel_btn()
{
    // Create the cancel button
    GtkWidget *cancel_btn = gtk_button_new_with_label("Cancel");
    // Set the size of the button
    gtk_widget_set_size_request(GTK_WIDGET(cancel_btn), 150, 50);
    // Connect signal handlers for mouse enter and leave events on the button
    g_signal_connect(G_OBJECT(cancel_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(cancel_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    // Connect a signal handler to the "clicked" signal of the button
    g_signal_connect(G_OBJECT(cancel_btn), "clicked", G_CALLBACK(destroy_popup_window), NULL);
    // Add CSS classes to the button for styling purposes
    add_class(cancel_btn, "btn");
    add_class(cancel_btn, "btn--dark-blue");

    return cancel_btn;
}

// Function definition to pack buttons into the button box
static void pack_buttons_into_btn_box(GtkWidget *btn_box, GtkWidget *confirm_delete_account_btn, GtkWidget *cancel_btn)
{
    gtk_box_pack_end(GTK_BOX(btn_box), confirm_delete_account_btn, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(btn_box), cancel_btn, FALSE, FALSE, 0);
}

// Function definition to pack content into the confirm delete account box
static void pack_content_into_confirm_delete_account_box(GtkWidget *confirm_delete_account_box, GtkWidget *confirm_delete_account_title, GtkWidget *confirm_delete_account_label, GtkWidget *btn_box)
{
    gtk_box_pack_start(GTK_BOX(confirm_delete_account_box), confirm_delete_account_title, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(confirm_delete_account_box), confirm_delete_account_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(confirm_delete_account_box), btn_box, FALSE, FALSE, 0);
}

// Function to build confirm delete account window
void build_confirm_delete_account_window(GtkWidget *widget, gpointer data)
{
    if (widget)
    { }
    (void)data;

    // Create a popup window for confirming account deletion
    GtkWidget *popup_window = create_popup_window(400, 0);
    GtkWidget *confirm_delete_account_box = create_confirm_delete_account_box(popup_window);

    // Create and set the title label for the confirmation window
    GtkWidget *confirm_delete_account_title = create_confirm_delete_account_title();

    // Create and set the label for the confirmation message
    GtkWidget *confirm_delete_account_label = create_confirm_delete_account_label();

    // Create the button box for confirming or canceling the account deletion
    GtkWidget *btn_box = create_confirm_delete_account_btn_box();

    // Create the delete button and connect its signal to the delete_account_btn_click function
    GtkWidget *confirm_delete_account_btn = create_confirm_delete_account_btn();

    // Create the cancel button and connect its signal to the destroy_popup_window function
    GtkWidget *cancel_btn = create_cancel_btn();

    // Pack the buttons into the button box
    pack_buttons_into_btn_box(btn_box, confirm_delete_account_btn, cancel_btn);

    // Pack the title, message, and button box into the confirmation box
    pack_content_into_confirm_delete_account_box(confirm_delete_account_box, confirm_delete_account_title, confirm_delete_account_label, btn_box);

    // Show the popup window and set focus to it
    gtk_widget_show_all(popup_window);
    gtk_widget_grab_focus(popup_window);
}
