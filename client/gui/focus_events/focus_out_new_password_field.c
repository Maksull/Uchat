#include "../../inc/client.h"

// Function to validate the content of the new password field and update its corresponding notification label
void validate_new_password_field(GtkWidget *toplevel)
{
    // Find the new password field and the corresponding notification label within the top-level window
    GtkWidget *new_password_field = get_widget_by_name_r(toplevel, "new_password_field");
    GtkWidget *new_password_notify_label = get_widget_by_name_r(toplevel, "new_password_notify_label");
    // Validate the content of the new password field
    validate_password_field(new_password_field, new_password_notify_label);
}

// Function to handle focus out new password field
void focus_out_new_password_field(GtkWidget *widget, gpointer data)
{
    (void)data;
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget); // Get the top-level window containing the widget

    // Validate the new password field and its corresponding notification label within the top-level window
    validate_new_password_field(toplevel);
}
