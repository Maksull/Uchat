#include "../inc/client.h"

// Function to handle build change password window
void build_change_password_window(GtkWidget *widget, gpointer data) {
    if (widget){};
    (void)data;

    // Create the popup window and the containing box
    GtkWidget *popup_window = create_popup_window(450, 0);
    GtkWidget *change_password_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    // Add the containing box to the popup window and set CSS classes
    gtk_container_add(GTK_CONTAINER(popup_window), change_password_box);
    add_class(change_password_box, "popup_menu");
    add_class(change_password_box, "edit_profile_menu");

    // Create labels and entry fields for current password, new password, and re-enter new password
    GtkWidget *change_password_title = gtk_label_new("Change password");
    gtk_widget_set_halign(GTK_WIDGET(change_password_title), GTK_ALIGN_CENTER);
    add_class(change_password_title, "popup_window_title");

    GtkWidget *current_password_label = gtk_label_new("Current password:");
    gtk_widget_set_halign(GTK_WIDGET(current_password_label), GTK_ALIGN_START);
    add_class(current_password_label, "input-field_title");
    GtkWidget *current_password_field = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(current_password_field), false);
    gtk_widget_set_name(current_password_field, "current_password_field");
    gtk_entry_set_placeholder_text(GTK_ENTRY(current_password_field), "Current password");
    g_signal_connect(G_OBJECT(current_password_field), "focus-out-event", G_CALLBACK(focus_out_current_password_field), NULL);
    add_class(current_password_field, "input-field");
    add_class(current_password_field, "input-field--password");

    GtkWidget *current_password_notify_label = gtk_label_new(" ");
    gtk_widget_set_halign(current_password_notify_label, GTK_ALIGN_START);
    gtk_widget_set_name(current_password_notify_label, "current_password_notify_label");
    add_class(current_password_notify_label, "notify-label");

    GtkWidget *new_password_label = gtk_label_new("New password:");
    gtk_widget_set_halign(GTK_WIDGET(new_password_label), GTK_ALIGN_START);
    add_class(new_password_label, "input-field_title");
    GtkWidget *new_password_field = gtk_entry_new();
    g_signal_connect(G_OBJECT(new_password_field), "focus-out-event", G_CALLBACK(focus_out_new_password_field), NULL);
    gtk_entry_set_visibility(GTK_ENTRY(new_password_field), false);
    gtk_widget_set_name(new_password_field, "new_password_field");
    gtk_entry_set_placeholder_text(GTK_ENTRY(new_password_field), "New password");
    add_class(new_password_field, "input-field");
    add_class(new_password_field, "input-field--password");

    GtkWidget *new_password_notify_label = gtk_label_new(" ");
    gtk_widget_set_halign(new_password_notify_label, GTK_ALIGN_START);
    gtk_widget_set_name(new_password_notify_label, "new_password_notify_label");
    add_class(new_password_notify_label, "notify-label");

    GtkWidget *re_new_password_label = gtk_label_new("Repeat password:");
    gtk_widget_set_halign(GTK_WIDGET(re_new_password_label), GTK_ALIGN_START);
    add_class(re_new_password_label, "input-field_title");
    GtkWidget *re_new_password_field = gtk_entry_new();
    g_signal_connect(G_OBJECT(re_new_password_field), "focus-out-event", G_CALLBACK(focus_out_re_new_password_field), NULL);
    gtk_entry_set_visibility(GTK_ENTRY(re_new_password_field), false);
    gtk_widget_set_name(re_new_password_field, "re_new_password_field");
    gtk_entry_set_placeholder_text(GTK_ENTRY(re_new_password_field), "Password");
    add_class(re_new_password_field, "input-field");
    add_class(re_new_password_field, "input-field--password");

    GtkWidget *re_new_password_notify_label = gtk_label_new(" ");
    gtk_widget_set_halign(re_new_password_notify_label, GTK_ALIGN_START);
    gtk_widget_set_name(re_new_password_notify_label, "re_new_password_notify_label");
    add_class(re_new_password_notify_label, "notify-label");

    // Create a box for buttons
    GtkWidget *btn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_halign(GTK_WIDGET(btn_box), GTK_ALIGN_CENTER);
    add_class(btn_box, "popup_btn_box");

    // Create the "Submit" button
    GtkWidget *change_password_btn = gtk_button_new_with_label("Submit");
    gtk_widget_set_size_request(GTK_WIDGET(change_password_btn), 150, 50);
    g_signal_connect(G_OBJECT(change_password_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(change_password_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(change_password_btn), "clicked", G_CALLBACK(change_password_btn_click), NULL);
    add_class(change_password_btn, "btn");
    add_class(change_password_btn, "btn--blue");

    // Create the "Cancel" button
    GtkWidget *cancel_btn = gtk_button_new_with_label("Cancel");
    gtk_widget_set_size_request(GTK_WIDGET(cancel_btn), 150, 50);
    g_signal_connect(G_OBJECT(cancel_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(cancel_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(cancel_btn), "clicked", G_CALLBACK(destroy_popup_window), NULL);
    add_class(cancel_btn, "btn");
    add_class(cancel_btn, "btn--dark-blue");

    // Pack buttons into the button box
    gtk_box_pack_end(GTK_BOX(btn_box), change_password_btn, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(btn_box), cancel_btn, FALSE, FALSE, 0);

    // Pack all widgets into the change password box
    gtk_box_pack_start(GTK_BOX(change_password_box), change_password_title, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_password_box), current_password_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_password_box), current_password_field, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_password_box), current_password_notify_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_password_box), new_password_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_password_box), new_password_field, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_password_box), new_password_notify_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_password_box), re_new_password_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_password_box), re_new_password_field, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_password_box), re_new_password_notify_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_password_box), btn_box, FALSE, FALSE, 0);

    // Show all widgets in the popup window and set focus on it
    gtk_widget_show_all(popup_window);
    gtk_widget_grab_focus(popup_window);
}
