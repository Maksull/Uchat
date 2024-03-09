#include "../inc/client.h"

// Function to add a CSS class to a GTK widget
void focus_out_login_field(GtkWidget *widget, gpointer data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget); // Get the top-level window containing the widget
    (void)data;

    // Find the login field and the corresponding notification label within the top-level window
    GtkWidget *login_field = get_widget_by_name_r(toplevel, "login_field");
    GtkWidget *login_notify_label = get_widget_by_name_r(toplevel, "login_notify_label");
    validate_name_field(login_field, login_notify_label); // Validate the content of the login field and update the notification label
}
