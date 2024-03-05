#include "../inc/client.h"

// Recursive function to get a widget by name within a container
GtkWidget *get_widget_by_name_r(GtkWidget *container, char *name)
{
    GtkWidget *result = NULL; // Result widget
    GList *children = NULL; // List of children widgets

    if (GTK_IS_CONTAINER(container)) // Check if container is a GTK container
    {
        children = gtk_container_get_children(GTK_CONTAINER(container)); // Get children of the container
    }
    else
    {
        return NULL; // Return NULL if container is not a GTK container
    }

    // Iterate through the children widgets
    while (children)
    {
        // Check if the name of the current widget matches the desired name
        if (!strcmp(gtk_widget_get_name(GTK_WIDGET(children->data)), name))
        {
            result = GTK_WIDGET(children->data); // Set result to the current widget
            break; // Exit the loop
        }
        // Check if the current widget is a container and search recursively within it
        else if (GTK_IS_CONTAINER(children->data))
        {
            result = get_widget_by_name_r(children->data, name); // Recursively search for the widget
            if (result != NULL)
                break; // Exit the loop if the widget is found
        }

        children = children->next; // Move to the next child widget
    }

    g_list_free(g_steal_pointer(&children)); // Free the memory allocated for the list of children

    return result; // Return the result widget
}
