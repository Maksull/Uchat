#include "../inc/client.h"

// Function to get widget by its name
GtkWidget *get_widget_by_name(GtkWidget *container, char *name)
{
    GtkWidget *result = NULL; // Pointer to the found widget
    GList *children = NULL; // Pointer to a list of child widgets

    // Check if the provided container is a valid GTK container
    if (GTK_IS_CONTAINER(container))
    {
        children = gtk_container_get_children(GTK_CONTAINER(container)); // Retrieve a list of children widgets from the container
    }
    else {
        return NULL; // Return NULL if the provided container is not a valid GTK container
    }

    // Iterate through the list of children widgets
    while (children)
    {
        // Check if the name of the current child widget matches the specified name
        if (!mx_strcmp(gtk_widget_get_name(GTK_WIDGET(children->data)), name))
        {
            result = GTK_WIDGET(children->data); // If found, assign the found widget to 'result'
            break;
        }

        children = children->next; // Move to the next child widget in the list
    }
    g_list_free(g_steal_pointer(&children)); // Free the memory allocated for the list of children widgets

    return result;
}
