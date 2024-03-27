#include "../../inc/client.h"

// Function to build the authorization window
void build_authorization_window()
{
    if (main_window) // Check if main_window exists
    {
        gtk_widget_destroy(main_window); // Destroy the existing main_window if it exists
    }

    main_window = create_new_window("Authorization", 500, 0, false); // Create a new main_window

    GtkWidget *main_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); // Create a vertical box for main area
    gtk_widget_set_name(main_area, "main_area"); // Set name for styling
    gtk_container_add(GTK_CONTAINER(main_window), main_area); // Add main_area to main_window

    build_login_menu(); // Build the login menu components
    gtk_widget_show_all(main_window); // Show all widgets in the main_window
}
