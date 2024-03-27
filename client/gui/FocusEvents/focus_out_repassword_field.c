#include "../../inc/client.h"

// Function to focus out repassword field
void focus_out_repassword_field(GtkWidget *widget, gpointer data)
{
    if (widget) { }
    (void)data;
    // Find the password field, re-enter password field, and the corresponding notification label within the main window
    GtkWidget *password_field = get_widget_by_name_r(main_window, "password_field");
    GtkWidget *repassword_field = get_widget_by_name_r(main_window, "repassword_field");
    GtkWidget *repassword_notify_label = get_widget_by_name_r(main_window, "repassword_notify_label");
    validate_repassword_field(password_field, repassword_field, repassword_notify_label); // Validate the content of the re-enter password field and update the notification label
}
