#include "../../inc/client.h"

// Function to validate the content of the username field and update its corresponding notification label
void validate_username_field_main_window()
{
    // Find the username field and the corresponding notification label within the main window
    GtkWidget *username_field = get_widget_by_name_r(main_window, "username_field");
    GtkWidget *username_notify_label = get_widget_by_name_r(main_window, "username_notify_label");
    // Validate the content of the username field and update the notification label
    validate_name_field(username_field, username_notify_label);
}

// Function to handle focus out the username field
void focus_out_username_field(GtkWidget *widget, gpointer data)
{
    if (widget)
    {
    }
    (void)data;

    // Validate the username field and update its corresponding notification label
    validate_username_field_main_window();
}
