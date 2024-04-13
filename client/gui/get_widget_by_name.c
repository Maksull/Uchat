#include "../inc/client.h"

// Function to compare widget names
gboolean widget_name_matches(GtkWidget *widget, const gchar *name)
{
    return gtk_widget_get_name(widget) && strcmp(gtk_widget_get_name(widget), name) == 0;
}

// Function to search for a widget by name within a list of widgets
GtkWidget *search_widget_by_name(GList *widgets, const gchar *name)
{
    GtkWidget *result = NULL;
    for (GList *iter = widgets; iter != NULL; iter = g_list_next(iter))
    {
        GtkWidget *widget = GTK_WIDGET(iter->data);
        if (widget_name_matches(widget, name))
        {
            result = widget;
            break;
        }
    }

    return result;
}

// Function to get a widget by name within a container
GtkWidget *get_widget_by_name(GtkWidget *container, const gchar *name)
{
    GtkWidget *result = NULL;
    if (!GTK_IS_CONTAINER(container))
        return NULL;

    GList *children = gtk_container_get_children(GTK_CONTAINER(container));
    result = search_widget_by_name(children, name);
    g_list_free(children);
    
    return result;
}