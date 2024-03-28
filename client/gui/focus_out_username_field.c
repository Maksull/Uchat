#include "../inc/client.h"

// Function to focus out username field
void focus_out_username_field(GtkWidget *widget, gpointer data)
{
    if (widget) { }
    (void)data;

    // Find the username field and the corresponding notification label within the main window
    GtkWidget *username_field = get_widget_by_name_r(main_window, "username_field");
    GtkWidget *username_notify_label = get_widget_by_name_r(main_window, "username_notify_label");
    validate_name_field(username_field, username_notify_label); // Validate the content of the username field and update the notification label
}
