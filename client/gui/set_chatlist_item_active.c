#include "../inc/client.h"

// Function to set chatlist item active
void set_chatlist_item_active(GtkWidget *widget)
{
    GtkWidget *chatlist_container = gtk_widget_get_parent(widget); // Get the parent container of the selected chat list item

    GList *children = gtk_container_get_children(GTK_CONTAINER(chatlist_container)); // Get the list of children widgets in the chatlist_container
    // Iterate through each child widget
    while (children)
    {
        remove_class(GTK_WIDGET(children->data), "active"); // Remove the "active" class from the current child widget
        children = children->next; // Move to the next child widget
    }
    }
    g_list_free(g_steal_pointer(&children)); // Free the memory allocated for the list of children widgets

    // gtk_container_foreach(GTK_CONTAINER(chatlist_container), (GtkCallback)remove_class, "active");
    add_class(widget, "active"); // Add the "active" class to the selected chat list item
}
