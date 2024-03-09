#include "../inc/client.h"

// Function to build confirm delete account window
void build_confirm_delete_account_window(GtkWidget *widget, gpointer data) {
    if(widget){}
    (void)data;

    // Create a popup window for confirming account deletion
    GtkWidget *popup_window = create_popup_window(400, 0);
    GtkWidget *confirm_delete_account_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    // Add the confirmation box to the popup window and set CSS classes
    gtk_container_add(GTK_CONTAINER(popup_window), confirm_delete_account_box);
    add_class(confirm_delete_account_box, "popup_menu");
    add_class(confirm_delete_account_box, "edit_profile_menu");

    // Create and set the title label for the confirmation window
    GtkWidget *confirm_delete_account_title = gtk_label_new("Delete account");
    gtk_widget_set_halign(GTK_WIDGET(confirm_delete_account_title), GTK_ALIGN_CENTER);
    add_class(confirm_delete_account_title, "popup_window_title");

    // Create and set the label for the confirmation message
    GtkWidget *confirm_delete_account_label = gtk_label_new("Are you sure you want to delete account?");
    gtk_widget_set_halign(GTK_WIDGET(confirm_delete_account_label), GTK_ALIGN_CENTER);
    add_class(confirm_delete_account_label, "confirm_text");

    // Create the button box for confirming or canceling the account deletion
    GtkWidget *btn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_halign(GTK_WIDGET(btn_box), GTK_ALIGN_CENTER);
    add_class(btn_box, "popup_btn_box");

    // Create the delete button and connect its signal to the delete_account_btn_click function
    GtkWidget *confirm_delete_account_btn = gtk_button_new_with_label("Delete");
    gtk_widget_set_size_request(GTK_WIDGET(confirm_delete_account_btn), 150, 50);
    g_signal_connect(G_OBJECT(confirm_delete_account_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(confirm_delete_account_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(confirm_delete_account_btn), "clicked", G_CALLBACK(delete_account_btn_click), NULL);
    add_class(confirm_delete_account_btn, "btn");
    add_class(confirm_delete_account_btn, "btn--blue");

    // Create the cancel button and connect its signal to the destroy_popup_window function
    GtkWidget *cancel_btn = gtk_button_new_with_label("Cancel");
    gtk_widget_set_size_request(GTK_WIDGET(cancel_btn), 150, 50);
    g_signal_connect(G_OBJECT(cancel_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(cancel_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(cancel_btn), "clicked", G_CALLBACK(destroy_popup_window), NULL);
    add_class(cancel_btn, "btn");
    add_class(cancel_btn, "btn--dark-blue");

    // Pack the buttons into the button box
    gtk_box_pack_end(GTK_BOX(btn_box), confirm_delete_account_btn, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(btn_box), cancel_btn, FALSE, FALSE, 0);

    // Pack the title, message, and button box into the confirmation box
    gtk_box_pack_start(GTK_BOX(confirm_delete_account_box), confirm_delete_account_title, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(confirm_delete_account_box), confirm_delete_account_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(confirm_delete_account_box), btn_box, FALSE, FALSE, 0);

    // Show the popup window and set focus to it
    gtk_widget_show_all(popup_window);
    gtk_widget_grab_focus(popup_window);
}
