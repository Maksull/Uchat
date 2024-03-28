#include "../../inc/client.h"

// Function to focus out password field
void focus_out_password_field(GtkWidget *widget, gpointer data)
{
    if (widget) { }
    (void)data;

    // Find the password field and the corresponding notification label within the main window
    GtkWidget *password_field = get_widget_by_name_r(main_window, "password_field");
    GtkWidget *password_notify_label = get_widget_by_name_r(main_window, "password_notify_label");
    validate_password_field(password_field, password_notify_label); // Validate the content of the password field and update the notification label
}
