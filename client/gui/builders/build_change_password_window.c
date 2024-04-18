#include "../../inc/client.h"

// Function definition to create and configure the title label of the change password window
static GtkWidget *create_and_configure_change_password_title()
{
    // Create a label for the title of the change password window
    GtkWidget *change_password_title = gtk_label_new("Change password");
    // Set the label's horizontal alignment to center
    gtk_widget_set_halign(GTK_WIDGET(change_password_title), GTK_ALIGN_CENTER);
    // Add a CSS class to the title label for styling purposes
    add_class(change_password_title, "popup_window_title");

    return change_password_title;
}

// Function definition to create and configure the "Current password" label and entry field
static void create_and_configure_current_password_field(GtkWidget **current_password_label_ptr, GtkWidget **current_password_field_ptr)
{
    // Create a label for the "Current password" field
    *current_password_label_ptr = gtk_label_new("Current password:");
    // Set the label's horizontal alignment to start
    gtk_widget_set_halign(GTK_WIDGET(*current_password_label_ptr), GTK_ALIGN_START);
    // Add a CSS class to the label for styling purposes
    add_class(*current_password_label_ptr, "input-field_title");

    // Create a new entry field for the current password
    *current_password_field_ptr = gtk_entry_new();
    // Set the entry field to hide the input (for password security)
    gtk_entry_set_visibility(GTK_ENTRY(*current_password_field_ptr), false);
    // Set the name of the entry field for identification purposes
    gtk_widget_set_name(*current_password_field_ptr, "current_password_field");
    // Set a placeholder text for the entry field
    gtk_entry_set_placeholder_text(GTK_ENTRY(*current_password_field_ptr), "Current password");
    // Connect a signal handler to the "focus-out-event" signal of the entry field
    // This handler will be called when the entry field loses focus
    g_signal_connect(G_OBJECT(*current_password_field_ptr), "focus-out-event", G_CALLBACK(focus_out_current_password_field), NULL);
    // Add CSS classes to the entry field for styling purposes
    add_class(*current_password_field_ptr, "input-field");
    add_class(*current_password_field_ptr, "input-field--password");
}

// Function definition to create and configure the notification label related to the current password field
static GtkWidget *create_and_configure_current_password_notify_label()
{
    // Create a label for displaying notifications related to the current password field
    GtkWidget *current_password_notify_label = gtk_label_new(" ");
    // Set the label's horizontal alignment to start
    gtk_widget_set_halign(current_password_notify_label, GTK_ALIGN_START);
    // Set the name of the label for identification purposes
    gtk_widget_set_name(current_password_notify_label, "current_password_notify_label");
    // Add a CSS class to the label for styling purposes
    add_class(current_password_notify_label, "notify-label");

    return current_password_notify_label;
}

// Function definition to create and configure the label for the "New password" field
static GtkWidget *create_and_configure_new_password_label()
{
    // Create a label for the "New password" field
    GtkWidget *new_password_label = gtk_label_new("New password:");
    // Set the label's horizontal alignment to start
    gtk_widget_set_halign(GTK_WIDGET(new_password_label), GTK_ALIGN_START);
    // Add a CSS class to the label for styling purposes
    add_class(new_password_label, "input-field_title");

    return new_password_label;
}

// Function definition to create and configure the entry field for the new password
static GtkWidget *create_and_configure_new_password_field()
{
    // Create a new entry field for the new password
    GtkWidget *new_password_field = gtk_entry_new();
    // Connect a signal handler to the "focus-out-event" signal of the entry field
    // This handler will be called when the entry field loses focus
    g_signal_connect(G_OBJECT(new_password_field), "focus-out-event", G_CALLBACK(focus_out_new_password_field), NULL);
    // Set the entry field to hide the input (for password security)
    gtk_entry_set_visibility(GTK_ENTRY(new_password_field), false);
    // Set the name of the entry field for identification purposes
    gtk_widget_set_name(new_password_field, "new_password_field");
    // Set a placeholder text for the entry field
    gtk_entry_set_placeholder_text(GTK_ENTRY(new_password_field), "New password");
    // Add CSS classes to the entry field for styling purposes
    add_class(new_password_field, "input-field");
    add_class(new_password_field, "input-field--password");

    return new_password_field;
}

// Function definition to create and configure the notification label for the new password field
static GtkWidget *create_and_configure_new_password_notify_label()
{
    // Create a label for displaying notifications related to the new password field
    GtkWidget *new_password_notify_label = gtk_label_new(" ");
    // Set the label's horizontal alignment to start
    gtk_widget_set_halign(new_password_notify_label, GTK_ALIGN_START);
    // Set the name of the label for identification purposes
    gtk_widget_set_name(new_password_notify_label, "new_password_notify_label");
    // Add a CSS class to the label for styling purposes
    add_class(new_password_notify_label, "notify-label");

    return new_password_notify_label;
}

// Function definition to create and configure the label for the "Repeat password" field
static GtkWidget *create_and_configure_re_new_password_label()
{
    // Create a label for the "Repeat password" field
    GtkWidget *re_new_password_label = gtk_label_new("Repeat password:");
    // Set the label's horizontal alignment to start
    gtk_widget_set_halign(GTK_WIDGET(re_new_password_label), GTK_ALIGN_START);
    // Add a CSS class to the label for styling purposes
    add_class(re_new_password_label, "input-field_title");

    return re_new_password_label;
}

// Function definition to create and configure the entry field for repeating the new password
static GtkWidget *create_and_configure_re_new_password_field()
{
    // Create a new entry field for repeating the new password
    GtkWidget *re_new_password_field = gtk_entry_new();
    // Connect a signal handler to the "focus-out-event" signal of the entry field
    // This handler will be called when the entry field loses focus
    g_signal_connect(G_OBJECT(re_new_password_field), "focus-out-event", G_CALLBACK(focus_out_re_new_password_field), NULL);
    // Set the entry field to hide the input (for password security)
    gtk_entry_set_visibility(GTK_ENTRY(re_new_password_field), false);
    // Set the name of the entry field for identification purposes
    gtk_widget_set_name(re_new_password_field, "re_new_password_field");
    // Set a placeholder text for the entry field
    gtk_entry_set_placeholder_text(GTK_ENTRY(re_new_password_field), "Password");
    // Add CSS classes to the entry field for styling purposes
    add_class(re_new_password_field, "input-field");
    add_class(re_new_password_field, "input-field--password");

    return re_new_password_field;
}

// Function definition to create and configure the notification label for the re-enter new password field
static GtkWidget *create_and_configure_re_new_password_notify_label()
{
    // Create a label for displaying notifications related to the re-enter new password field
    GtkWidget *re_new_password_notify_label = gtk_label_new(" ");
    // Set the label's horizontal alignment to start
    gtk_widget_set_halign(re_new_password_notify_label, GTK_ALIGN_START);
    // Set the name of the label for identification purposes
    gtk_widget_set_name(re_new_password_notify_label, "re_new_password_notify_label");
    // Add a CSS class to the label for styling purposes
    add_class(re_new_password_notify_label, "notify-label");

    return re_new_password_notify_label;
}

// Function definition to create and configure the button box
static GtkWidget *create_and_configure_btn_box()
{
    // Create a horizontal box to hold the buttons
    GtkWidget *btn_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    // Set the horizontal alignment of the button box to center
    gtk_widget_set_halign(GTK_WIDGET(btn_box), GTK_ALIGN_CENTER);
    // Add a CSS class to the button box for styling purposes
    add_class(btn_box, "popup_btn_box");

    return btn_box;
}

// Function definition to create and configure the "Submit" button
static GtkWidget *create_and_configure_change_password_btn()
{
    // Create the "Submit" button
    GtkWidget *change_password_btn = gtk_button_new_with_label("Submit");
    // Set the size of the button
    gtk_widget_set_size_request(GTK_WIDGET(change_password_btn), 150, 50);
    // Connect signal handlers for mouse enter and leave events on the button
    // These handlers will be called when the mouse enters or leaves the button
    g_signal_connect(G_OBJECT(change_password_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(change_password_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    // Connect a signal handler to the "clicked" signal of the button
    // This handler will be called when the button is clicked
    g_signal_connect(G_OBJECT(change_password_btn), "clicked", G_CALLBACK(change_password_btn_click), NULL);
    // Add CSS classes to the button for styling purposes
    add_class(change_password_btn, "btn");
    add_class(change_password_btn, "btn--blue");

    return change_password_btn;
}

// Function definition to create and configure the "Cancel" button
static GtkWidget *create_and_configure_cancel_btn()
{
    // Create the "Cancel" button
    GtkWidget *cancel_btn = gtk_button_new_with_label("Cancel");
    // Set the size of the button
    gtk_widget_set_size_request(GTK_WIDGET(cancel_btn), 150, 50);
    // Connect signal handlers for mouse enter and leave events on the button
    g_signal_connect(G_OBJECT(cancel_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(cancel_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    // Connect a signal handler to the "clicked" signal of the button
    // This handler will be called when the button is clicked
    g_signal_connect(G_OBJECT(cancel_btn), "clicked", G_CALLBACK(destroy_popup_window), NULL);
    // Add CSS classes to the button for styling purposes
    add_class(cancel_btn, "btn");
    add_class(cancel_btn, "btn--dark-blue");

    return cancel_btn;
}

// Function definition to pack all widgets into the change password box
static void pack_widgets_into_change_password_box(GtkWidget *change_password_box, GtkWidget *change_password_title, GtkWidget *current_password_label, GtkWidget *current_password_field, GtkWidget *current_password_notify_label, GtkWidget *new_password_label, GtkWidget *new_password_field, GtkWidget *new_password_notify_label, GtkWidget *re_new_password_label, GtkWidget *re_new_password_field, GtkWidget *re_new_password_notify_label, GtkWidget *btn_box)
{
    // Pack all the widgets into the change password box
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
}

// Function to handle building the change password window
void build_change_password_window(GtkWidget *widget, gpointer data)
{
    // This is a safety check to ensure that the function is called with a valid widget
    if (widget)
    {
    }
    // Ignore the data parameter since it's not used in this function
    (void)data;

    // Create a new popup window with a width of 450 pixels and a default height
    GtkWidget *popup_window = create_popup_window(450, 0);
    // Create a new vertical box to hold the components of the change password window
    GtkWidget *change_password_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    // Add the change password box to the popup window as a child widget
    gtk_container_add(GTK_CONTAINER(popup_window), change_password_box);
    // Add CSS classes to the change password box for styling purposes
    add_class(change_password_box, "popup_menu");
    add_class(change_password_box, "edit_profile_menu");

    // Create and configure the title label for the change password window
    GtkWidget *change_password_title = create_and_configure_change_password_title();

    // Create labels, entry fields, notification labels, and buttons for the change password window
    GtkWidget *current_password_label, *current_password_field;
    create_and_configure_current_password_field(&current_password_label, &current_password_field);

    // Create a label for displaying notifications related to the current password field
    GtkWidget *current_password_notify_label = create_and_configure_current_password_notify_label();

    // Create and configure the label for the "New password" field
    GtkWidget *new_password_label = create_and_configure_new_password_label();

    // Create and configure the entry field for the new password
    GtkWidget *new_password_field = create_and_configure_new_password_field();

    // Create a label for displaying notifications related to the new password field
    GtkWidget *new_password_notify_label = create_and_configure_new_password_notify_label();

    // Create a label for the "Repeat password" field
    GtkWidget *re_new_password_label = create_and_configure_re_new_password_label();

    // Create a new entry field for repeating the new password
    GtkWidget *re_new_password_field = create_and_configure_re_new_password_field();

    // Create a label for displaying notifications related to the re-enter new password field
    GtkWidget *re_new_password_notify_label = create_and_configure_re_new_password_notify_label();

    // Create a horizontal box to hold the buttons
    GtkWidget *btn_box = create_and_configure_btn_box();

    // Create the "Submit" button
    GtkWidget *change_password_btn = create_and_configure_change_password_btn();

    // Create the "Cancel" button
    GtkWidget *cancel_btn = create_and_configure_cancel_btn();

    // Pack the buttons into the button box
    pack_buttons_into_button_box(btn_box, change_password_btn, cancel_btn);

    // Pack all the widgets (labels, entry fields, notification labels, and button box) into the change password box
    pack_widgets_into_change_password_box(change_password_box, change_password_title, current_password_label, current_password_field, current_password_notify_label, new_password_label, new_password_field, new_password_notify_label, re_new_password_label, re_new_password_field, re_new_password_notify_label, btn_box);

    // Show all widgets in the popup window
    gtk_widget_show_all(popup_window);
    // Set the keyboard focus to the popup window
    gtk_widget_grab_focus(popup_window);
}
