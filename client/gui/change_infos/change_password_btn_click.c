#include "../../inc/client.h"

// Function to get password field widgets and their notification labels
static void get_password_fields_and_labels(GtkWidget *toplevel, GtkWidget **current_password_field, GtkWidget **current_password_notify_label, GtkWidget **new_password_field, GtkWidget **new_password_notify_label, GtkWidget **re_new_password_field, GtkWidget **re_new_password_notify_label)
{
    *current_password_field = get_widget_by_name_r(toplevel, "current_password_field");
    *current_password_notify_label = get_widget_by_name_r(toplevel, "current_password_notify_label");
    *new_password_field = get_widget_by_name_r(toplevel, "new_password_field");
    *new_password_notify_label = get_widget_by_name_r(toplevel, "new_password_notify_label");
    *re_new_password_field = get_widget_by_name_r(toplevel, "re_new_password_field");
    *re_new_password_notify_label = get_widget_by_name_r(toplevel, "re_new_password_notify_label");
}

// Function to validate the content of the current password field
static bool validate_current_password(GtkWidget *current_password_field, GtkWidget *current_password_notify_label)
{
    bool current_password_field_valid = validate_password_field(current_password_field, current_password_notify_label);
    char *current_password = (char *)gtk_entry_get_text(GTK_ENTRY(current_password_field));

    if (current_password_field_valid)
    {
        if (mx_strcmp(current_password, utils->current_user->password) != 0)
        {
            set_field_error_style(current_password_field);
            set_notify_error_style(current_password_notify_label, "Incorrect password");

            return false;
        }
        else
        {
            set_field_success_style(current_password_field);
            set_notify_success_style(current_password_notify_label, "");
        }
    }

    return true;
}

// Function to handle the click event of the "Change Password" button
void change_password_btn_click(GtkWidget *widget, gpointer data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget);
    (void)data;

    GtkWidget *current_password_field, *current_password_notify_label, *new_password_field, *new_password_notify_label, *re_new_password_field, *re_new_password_notify_label;
    get_password_fields_and_labels(toplevel, &current_password_field, &current_password_notify_label, &new_password_field, &new_password_notify_label, &re_new_password_field, &re_new_password_notify_label);

    if (!validate_current_password(current_password_field, current_password_notify_label))
    {
        return;
    }

    // Validate the content of the new password and re-enter new password fields
    bool new_password_field_valid = validate_password_field(new_password_field, new_password_notify_label);
    bool re_new_password_field_valid = validate_repassword_field(new_password_field, re_new_password_field, re_new_password_notify_label);

    if (!current_password_field_valid || !new_password_field_valid || !re_new_password_field_valid)
    {
        return;
    }

    char *new_password = (char *)gtk_entry_get_text(GTK_ENTRY(new_password_field));
    // Send request to update user's password and handle the response
    int response_code = handle_edit_password_req(new_password, (char *)gtk_entry_get_text(GTK_ENTRY(current_password_field)));
    handle_edit_password_response_code(response_code, new_password_field, new_password_notify_label);
}
