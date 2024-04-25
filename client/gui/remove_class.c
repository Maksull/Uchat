#include "../inc/client.h"

// Function to remove a CSS class to a GTK widget
void remove_class(GtkWidget *widget, char *class_name)
{
    GtkStyleContext *context = gtk_widget_get_style_context(widget); // Get the style context of the widget
    gtk_style_context_remove_class(context, class_name); // Remove the specified CSS class to the widget
}
