#include "../inc/client.h"

// Function to handle clear search field
void clear_search_field(GtkWidget *widget, gpointer entry_field)
{
    if (widget){}
    gtk_entry_set_text(GTK_ENTRY(entry_field), ""); // Set empty string to the search field
}
