#include "../../inc/client.h"

// Function definition to create the vertical box container
static GtkWidget *create_change_login_box(GtkWidget *popup_window)
{
    GtkWidget *change_login_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); // Create a vertical box container for the elements
    gtk_container_add(GTK_CONTAINER(popup_window), change_login_box);       // Add the container to the popup window
    add_class(change_login_box, "popup_menu");                              // Add CSS class to the container

    return change_login_box;
}

// Function definition to create and configure the title label
static GtkWidget *create_and_configure_title_label(const gchar *text)
{
    GtkWidget *label = gtk_label_new(text);
    gtk_widget_set_halign(GTK_WIDGET(label), GTK_ALIGN_CENTER);
    add_class(label, "popup_window_title");

    return label;
}

// Function definition to create and configure the label and entry field for the new avatar path
static void create_and_configure_path_widgets(GtkWidget *container)
{
    // Create and configure the label
    GtkWidget *path_label = gtk_label_new("New avatar path:");
    gtk_widget_set_halign(GTK_WIDGET(path_label), GTK_ALIGN_START);
    add_class(path_label, "input-field_title");
    gtk_box_pack_start(GTK_BOX(container), path_label, FALSE, FALSE, 0);

    // Create and configure the entry field
    GtkWidget *path_field = gtk_entry_new();
    gtk_widget_set_name(path_field, "path_field");
    gtk_entry_set_placeholder_text(GTK_ENTRY(path_field), "Avatar path");
    add_class(path_field, "input-field");
    add_class(path_field, "input-field--name");
    gtk_box_pack_start(GTK_BOX(container), path_field, FALSE, FALSE, 0);
}

// Function definition to create and configure the notification label for the path field
static void create_and_configure_path_notify_label(GtkWidget *container)
{
    // Create and configure the notification label
    GtkWidget *path_notify_label = gtk_label_new(" ");
    gtk_widget_set_halign(path_notify_label, GTK_ALIGN_START);
    gtk_widget_set_name(path_notify_label, "path_notify_label");
    add_class(path_notify_label, "notify-label");
    gtk_box_pack_start(GTK_BOX(container), path_notify_label, FALSE, FALSE, 0);
}

// Function definition to create and configure the button box
static GtkWidget *create_and_configure_button_box(GtkWidget *container)
{
    // Create and configure the button box
    GtkWidget *btn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_halign(GTK_WIDGET(btn_box), GTK_ALIGN_CENTER);
    add_class(btn_box, "popup_btn_box");
    gtk_box_pack_start(GTK_BOX(container), btn_box, FALSE, FALSE, 0);

    return btn_box;
}

// Function definition to create and configure the Submit button
static GtkWidget *create_and_configure_submit_button(GtkWidget *container)
{
    // Create and configure the Submit button
    GtkWidget *change_login_btn = gtk_button_new_with_label("Submit");
    gtk_widget_set_size_request(GTK_WIDGET(change_login_btn), 150, 50);
    g_signal_connect(G_OBJECT(change_login_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(change_login_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(change_login_btn), "clicked", G_CALLBACK(change_avatar_btn_click), NULL);
    add_class(change_login_btn, "btn");
    add_class(change_login_btn, "btn--blue");
    gtk_box_pack_end(GTK_BOX(container), change_login_btn, FALSE, FALSE, 0);

    return change_login_btn;
}

// Function definition to create and configure the Cancel button
static GtkWidget *create_and_configure_cancel_button(GtkWidget *container)
{
    // Create and configure the Cancel button
    GtkWidget *cancel_btn = gtk_button_new_with_label("Cancel");
    gtk_widget_set_size_request(GTK_WIDGET(cancel_btn), 150, 50);
    g_signal_connect(G_OBJECT(cancel_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(cancel_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(cancel_btn), "clicked", G_CALLBACK(destroy_popup_window), NULL);
    add_class(cancel_btn, "btn");
    add_class(cancel_btn, "btn--dark-blue");
    gtk_box_pack_end(GTK_BOX(container), cancel_btn, FALSE, FALSE, 0);

    return cancel_btn;
}

// Function to build the window for avatar change
void build_change_avatar_window(GtkWidget *widget, gpointer data)
{
    if (widget)
    {
    };
    (void)data;

    GtkWidget *popup_window = create_popup_window(450, 0); // Create a popup window for changing the avatar

    // Create the vertical box container for the elements and add it to the popup window
    GtkWidget *change_login_box = create_change_login_box(popup_window);

    // Create and configure the title label
    GtkWidget *change_avatar_title = create_and_configure_title_label("Change avatar");

    // Create and configure the label and entry field for the new avatar path
    create_and_configure_path_widgets(change_login_box);

    // Create and configure the notification label for the path field
    create_and_configure_path_notify_label(change_login_box);

    // Create and configure the button box
    GtkWidget *btn_box = create_and_configure_button_box(change_login_box);

    // Create and configure the Submit button
    create_and_configure_submit_button(btn_box);

    // Create and configure the Cancel button
    create_and_configure_cancel_button(btn_box);

    // Pack all elements into the main container
    gtk_box_pack_start(GTK_BOX(change_login_box), change_avatar_title, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(change_login_box), btn_box, FALSE, FALSE, 0);

    // Show all elements in the popup window and set focus to it
    gtk_widget_show_all(popup_window);
    gtk_widget_grab_focus(popup_window);
}
