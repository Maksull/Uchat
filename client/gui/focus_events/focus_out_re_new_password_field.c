#include "../../inc/client.h"

// Function to validate the content of the "new password" and "re-enter new password" fields and update their corresponding notification label
void validate_re_new_password_fields(GtkWidget *toplevel)
{
    // Find the "new password" field, "re-enter new password" field, and the corresponding notification label within the top-level window
    GtkWidget *new_password_field = get_widget_by_name_r(toplevel, "new_password_field");
    GtkWidget *re_new_password_field = get_widget_by_name_r(toplevel, "re_new_password_field");
    GtkWidget *re_new_password_notify_label = get_widget_by_name_r(toplevel, "re_new_password_notify_label");
    // Validate the content of both the "new password" and "re-enter new password" fields
    validate_repassword_field(new_password_field, re_new_password_field, re_new_password_notify_label);
}

// Function to handle focus out the "re-enter new password" field
void focus_out_re_new_password_field(GtkWidget *widget, gpointer data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget); // Get the top-level window containing the widget
    (void)data;

    // Validate the "new password" and "re-enter new password" fields and update their corresponding notification label
    validate_re_new_password_fields(toplevel);
}
