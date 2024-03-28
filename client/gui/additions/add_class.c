#include "../../inc/client.h"

// Function to add a CSS class to a GTK widget
void add_class(GtkWidget *widget, char *class_name)
{
    GtkStyleContext *context = gtk_widget_get_style_context(widget); // Get the style context of the widget
    gtk_style_context_add_class(context, class_name);                // Add the specified CSS class to the widget
}
