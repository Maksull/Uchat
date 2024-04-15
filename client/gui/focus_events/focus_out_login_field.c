#include "../../inc/client.h"

// Function to find and validate the login field and its corresponding notification label within the top-level window
void validate_login_field(GtkWidget *toplevel)
{
    // Find the login field and the corresponding notification label within the top-level window
    GtkWidget *login_field = get_widget_by_name_r(toplevel, "login_field");
    GtkWidget *login_notify_label = get_widget_by_name_r(toplevel, "login_notify_label");
    // Validate the content of the login field and update the notification label
    validate_name_field(login_field, login_notify_label);
}

// Function to handle focus out login field
void focus_out_login_field(GtkWidget *widget, gpointer data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget); // Get the top-level window containing the widget
    (void)data;

    // Validate the login field and its corresponding notification label within the top-level window
    validate_login_field(toplevel);
}
