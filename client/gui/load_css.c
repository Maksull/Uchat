#include "../inc/client.h"

// Function to load css
void load_css()
{
    GtkCssProvider *styles = gtk_css_provider_new(); // Create a new GTK CSS provider
    gtk_css_provider_load_from_path(styles, "client/data/styles/main.css", NULL); // Load CSS styles from the specified file path
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(styles), GTK_STYLE_PROVIDER_PRIORITY_USER); // Add the CSS provider to the default screen's style context
}
