#include "../inc/client.h"

// Function to handle build change login window
void build_change_login_window(GtkWidget *widget, gpointer data)
{
    if (widget) {};
    (void)data;

    GtkWidget *popup_window = create_popup_window(450, 0);                  // Create a popup window for changing the login
    GtkWidget *change_login_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); // Create a vertical box container for the elements

    gtk_container_add(GTK_CONTAINER(popup_window), change_login_box); // Add the container to the popup window
    // Add CSS classes to the container
    add_class(change_login_box, "popup_menu");
    add_class(change_login_box, "edit_profile_menu");

    // Create and configure the title label
    GtkWidget *change_login_title = gtk_label_new("Change login");
    gtk_widget_set_halign(GTK_WIDGET(change_login_title), GTK_ALIGN_CENTER);
    add_class(change_login_title, "popup_window_title");

    // Create and configure the label and entry field for the new login
    GtkWidget *login_label = gtk_label_new("New login:");
    gtk_widget_set_halign(GTK_WIDGET(login_label), GTK_ALIGN_START);
    add_class(login_label, "input-field_title");
    GtkWidget *login_field = gtk_entry_new();
    gtk_widget_set_name(login_field, "login_field");
    gtk_entry_set_placeholder_text(GTK_ENTRY(login_field), "Login");
    g_signal_connect(G_OBJECT(login_field), "focus-out-event", G_CALLBACK(focus_out_login_field), NULL);
    add_class(login_field, "input-field");
    add_class(login_field, "input-field--name");

    // Create and configure the notification label for the login field
    GtkWidget *login_notify_label = gtk_label_new(" ");
    gtk_widget_set_halign(login_notify_label, GTK_ALIGN_START);
    gtk_widget_set_name(login_notify_label, "login_notify_label");
    add_class(login_notify_label, "notify-label");

    // Create a horizontal box container for buttons
    GtkWidget *btn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_halign(GTK_WIDGET(btn_box), GTK_ALIGN_CENTER);
    add_class(btn_box, "popup_btn_box");

    // Create and configure the Submit button
    GtkWidget *change_login_btn = gtk_button_new_with_label("Submit");
    gtk_widget_set_size_request(GTK_WIDGET(change_login_btn), 150, 50);
    g_signal_connect(G_OBJECT(change_login_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(change_login_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(change_login_btn), "clicked", G_CALLBACK(change_login_btn_click), NULL);
    add_class(change_login_btn, "btn");
    add_class(change_login_btn, "btn--blue");

    // Create and configure the Cancel button
    GtkWidget *cancel_btn = gtk_button_new_with_label("Cancel");
    gtk_widget_set_size_request(GTK_WIDGET(cancel_btn), 150, 50);
    g_signal_connect(G_OBJECT(cancel_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(cancel_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(cancel_btn), "clicked", G_CALLBACK(destroy_popup_window), NULL);
    add_class(cancel_btn, "btn");
    add_class(cancel_btn, "btn--dark-blue");

    // Pack buttons into the button box container
    gtk_box_pack_end(GTK_BOX(btn_box), change_login_btn, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(btn_box), cancel_btn, FALSE, FALSE, 0);

    // Pack all elements into the main container
    gtk_box_pack_start(GTK_BOX(change_login_box), change_login_title, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_login_box), login_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_login_box), login_field, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_login_box), login_notify_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_login_box), btn_box, FALSE, FALSE, 0);

    // Show all elements in the popup window and set focus to it
    gtk_widget_show_all(popup_window);
    gtk_widget_grab_focus(popup_window);
}
