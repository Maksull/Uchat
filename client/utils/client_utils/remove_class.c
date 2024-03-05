#include "../../inc/client.h"

// Remove a CSS class from a GTK widget
void remove_class(GtkWidget *widget, char *class_name)
{
    // Get the style context of the widget
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    // Remove the specified class from the style context
    gtk_style_context_remove_class(context, class_name);
}
