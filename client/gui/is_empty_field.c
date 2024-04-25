#include "../inc/client.h"

// Function to get the text from a GtkEntry widget
static char *get_entry_text(GtkWidget *entry)
{
    return (char *)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(entry)));
}

// Function to set an error style for a notification label
static void set_label_text(GtkWidget *notify_label, const gchar *message)
{
    gtk_label_set_text(GTK_LABEL(notify_label), message);
}

// Function to check if a field is empty and handle error styling and notification
bool is_empty_field(GtkWidget *field, GtkWidget *notify_label)
{
    char *text = get_entry_text(field); // Get the text from the text entry field

    // Check if the text is empty
    if (strlen(text) == 0)
    {
        add_class(field, "input-field--danger");                         // Set error style for the field
        set_label_text(notify_label, "This field is required!"); // Set notification label with a required message

        return true; // Field is empty
    }
    else
    {
        remove_class(field, "input-field--danger"); // Remove any error styles applied to the field
        set_label_text(notify_label, "");   // Clear the notification label

        return false; // Field is not empty
    }
}
