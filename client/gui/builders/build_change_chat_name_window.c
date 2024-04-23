#include "../../inc/client.h"

// Function definition to create and configure the title label
static GtkWidget *create_change_chat_name_title_label(const gchar *title_text)
{
    GtkWidget *change_chat_name_title = gtk_label_new(title_text);
    gtk_widget_set_halign(GTK_WIDGET(change_chat_name_title), GTK_ALIGN_CENTER);
    add_class(change_chat_name_title, "popup_window_title");

    return change_chat_name_title;
}

// Function definition to create and configure the label and entry field
static void create_and_configure_chat_name_widgets(GtkWidget **chat_name_label, GtkWidget **chat_name_field)
{
    // Create and configure the label for the new chat name
    *chat_name_label = gtk_label_new("New chat name:");
    gtk_widget_set_halign(GTK_WIDGET(*chat_name_label), GTK_ALIGN_START);
    add_class(*chat_name_label, "input-field_title");

    // Create and configure the entry field for the new chat name
    *chat_name_field = gtk_entry_new();
    gtk_widget_set_name(*chat_name_field, "chat_name_field");
    gtk_entry_set_placeholder_text(GTK_ENTRY(*chat_name_field), "Chat name");
    g_signal_connect(G_OBJECT(*chat_name_field), "focus-out-event", G_CALLBACK(focus_out_chat_name_field), NULL);
    add_class(*chat_name_field, "input-field-2");
}

// Function definition to create and configure the notification label
static GtkWidget *create_and_configure_chat_name_notify_label()
{
    GtkWidget *chat_name_notify_label = gtk_label_new(" ");
    gtk_widget_set_halign(chat_name_notify_label, GTK_ALIGN_START);
    gtk_widget_set_name(chat_name_notify_label, "chat_name_notify_label");
    add_class(chat_name_notify_label, "notify-label");

    return chat_name_notify_label;
}

// Function definition to create the button box container
static GtkWidget *create_button_box()
{
    GtkWidget *btn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_halign(GTK_WIDGET(btn_box), GTK_ALIGN_CENTER);
    add_class(btn_box, "popup_btn_box");

    return btn_box;
}

// Function definition to create the "Rename" button
static GtkWidget *create_rename_button()
{
    GtkWidget *change_chat_name_btn = gtk_button_new_with_label("Rename");
    gtk_widget_set_size_request(GTK_WIDGET(change_chat_name_btn), 150, 50);
    g_signal_connect(G_OBJECT(change_chat_name_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(change_chat_name_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(change_chat_name_btn), "clicked", G_CALLBACK(change_chat_name_btn_click), NULL);
    add_class(change_chat_name_btn, "btn");
    add_class(change_chat_name_btn, "btn--blue");

    return change_chat_name_btn;
}

// Function definition to create the "Cancel" button
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

// Function definition to pack buttons into the button box container
static void pack_buttons_into_box(GtkWidget *btn_box, GtkWidget *button1, GtkWidget *button2)
{
    gtk_box_pack_end(GTK_BOX(btn_box), button1, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(btn_box), button2, FALSE, FALSE, 0);
}

// Function definition to pack all elements into the main container
static void pack_elements_into_container(GtkWidget *container, GtkWidget *title, GtkWidget *label, GtkWidget *field, GtkWidget *notify_label, GtkWidget *btn_box)
{
    gtk_box_pack_start(GTK_BOX(container), title, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(container), label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(container), field, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(container), notify_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(container), btn_box, FALSE, FALSE, 0);
}

// Function to handle build change chat name window
void build_change_chat_name_window(GtkWidget *widget, gpointer data)
{
    if (widget)
    { }
    (void)data;

    GtkWidget *popup_window = create_popup_window(450, 0);                      // Create a popup window for changing the chat name
    GtkWidget *change_chat_name_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); // Create a vertical box container for the elements

    gtk_container_add(GTK_CONTAINER(popup_window), change_chat_name_box); // Add the container to the popup window
    // Add CSS classes to the container
    add_class(change_chat_name_box, "popup_menu");
    add_class(change_chat_name_box, "edit_profile_menu");

    // Create and configure the title label
    GtkWidget *change_chat_name_title = create_change_chat_name_title_label("Change chat name");

    // Create and configure the label and entry field for the new chat name
    GtkWidget *chat_name_label = NULL;
    GtkWidget *chat_name_field = NULL;
    create_and_configure_chat_name_widgets(&chat_name_label, &chat_name_field);

    // Create and configure the notification label for the chat name field
    GtkWidget *chat_name_notify_label = create_and_configure_chat_name_notify_label();

    // Create a horizontal box container for buttons
    GtkWidget *btn_box = create_button_box();

    // Create and configure the Rename button
    GtkWidget *change_chat_name_btn = create_rename_button();

    // Create and configure the Cancel button
    GtkWidget *cancel_btn = create_cancel_button();

    // Pack buttons into the button box container
    pack_buttons_into_box(btn_box, change_chat_name_btn, cancel_btn);

    // Pack all elements into the main container
    pack_elements_into_container(change_chat_name_box, change_chat_name_title, chat_name_label, chat_name_field, chat_name_notify_label, btn_box);

    // Show all elements in the popup window and set focus to it
    gtk_widget_show_all(popup_window);
    gtk_widget_grab_focus(popup_window);
}
