#include "../inc/client.h"

// Function to check if the field is empty
bool is_empty_field(GtkWidget *field, GtkWidget *notify_label)
{
    char *text = (char *)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(field))); // Get the text from the text entry field

    // Check if the text is empty
    if (!mx_strcmp(text, ""))
    {
        // Set error style for the field and notify label with a required message
        set_field_error_style(field);
        set_notify_error_style(notify_label, "This field is required!");

        return true; // Field is empty
    }
    else
    {
        // Remove any error styles applied to the field and clear the notification label
        remove_class(field, "input-field--danger");
        set_notify_error_style(notify_label, "");
        
        return false; // Field is not empty
    }
}
