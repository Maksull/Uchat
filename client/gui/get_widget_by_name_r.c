#include "../inc/client.h"

// Function to check if a widget's name matches the desired name
static gboolean widget_name_matches(GtkWidget *widget, const gchar *name)
{
    return gtk_widget_get_name(widget) && strcmp(gtk_widget_get_name(widget), name) == 0;
}

// Recursive function to search for a widget by name within a container
static GtkWidget *recursive_search_widget(GtkWidget *widget, const gchar *name)
{
    if (!GTK_IS_CONTAINER(widget))
    {
        return NULL;
    }

    GList *children = gtk_container_get_children(GTK_CONTAINER(widget));
    GtkWidget *result = NULL;

    for (GList *iter = children; iter != NULL; iter = g_list_next(iter))
    {
        GtkWidget *child = GTK_WIDGET(iter->data);
        if (widget_name_matches(child, name))
        {
            result = child;
            break;
        }
        else if (GTK_IS_CONTAINER(child))
        {
            result = recursive_search_widget(child, name);
            if (result != NULL)
            {
                break;
            }
        }
    }

    g_list_free(children);
    
    return result;
}

// Function to get a widget by name within a container
GtkWidget *get_widget_by_name_r(GtkWidget *container, const gchar *name)
{
    return recursive_search_widget(container, name);
}
