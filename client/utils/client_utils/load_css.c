#include "../../inc/client.h"

// Load CSS styles
void load_css()
{
    GtkCssProvider *styles = gtk_css_provider_new(); // Create a new CSS provider
    gtk_css_provider_load_from_path(styles, "client/data/styles/main.css", NULL); // Load CSS styles from file
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(styles), GTK_STYLE_PROVIDER_PRIORITY_USER); // Add CSS provider to the default screen
}
