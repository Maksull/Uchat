#include "../inc/client.h"

// Function to add a CSS class to a GTK widget
void search_field_change_event(GtkWidget *widget, gpointer data)
{
    char *search_str = (char*)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(widget))); // Retrieve the search string from the search field
    // Check if the search string is empty
    if (!mx_strcmp(search_str, ""))
    {
        update_chatlist(); // If search string is empty, update the chatlist with the original list of chats
        update_chatlist();
    }
    else
    {
        update_found_chats(search_str); // If search string is not empty, update the chatlist with the chats found based on the search string
    }
    (void)data;
}
