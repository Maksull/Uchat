#include "../../inc/client.h"

// Function to validate the content of the password field and update its corresponding notification label
static void validate_password_main_window()
{
    // Find the password field and the corresponding notification label within the main window
    GtkWidget *password_field = get_widget_by_name_r(main_window, "password_field");
    GtkWidget *password_notify_label = get_widget_by_name_r(main_window, "password_notify_label");
    // Validate the content of the password field and update the notification label
    validate_password_field(password_field, password_notify_label);
}

// Function to focus out password field
void focus_out_password_field(GtkWidget *widget, gpointer data)
{
    if (widget)
    { }
    (void)data;

    // Validate the password field and its corresponding notification label within the main window
    validate_password_main_window();
}
