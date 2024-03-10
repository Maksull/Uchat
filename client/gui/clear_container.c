#include "../inc/client.h"

// Function to clear container
void clear_container(GtkWidget *container)
{
    gtk_container_foreach(GTK_CONTAINER(container), (GtkCallback)gtk_widget_destroy, NULL); // clear
}
