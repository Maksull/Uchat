#include "../inc/client.h"

// Function to compare widget names
static gboolean widget_name_matches(GtkWidget *widget, char *name)
{
    return gtk_widget_get_name(widget) && strcmp(gtk_widget_get_name(widget), name) == 0;
}

// Function to search for a widget by name within a list of widgets
static GtkWidget *search_widget_by_name(GList *widgets, char *name)
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
GtkWidget *get_widget_by_name(GtkWidget *container, char *name)
{
    GtkWidget *result = NULL;
    if (!GTK_IS_CONTAINER(container))
        return NULL;

    GList *children = gtk_container_get_children(GTK_CONTAINER(container));
    result = search_widget_by_name(children, name);
    g_list_free(children);
    
    return result;
}
