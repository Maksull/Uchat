#include "../../inc/client.h"

// Add a CSS class to a GTK widget
void add_class(GtkWidget *widget, char *class_name)
{
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_class(context, class_name);
}
