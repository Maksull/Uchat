#include "../../inc/client.h"

// Function to build chat window
void build_chat_window()
{
    // Check if the main window exists and destroy it if it does
    if (main_window)
    {
        gtk_widget_destroy(main_window);
    }

    main_window = create_new_window("UChat", 500, 0, true); // Create a new main window with the title "UChat"

    // Create a new main area widget to hold the chat interface components
    GtkWidget *main_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_name(main_area, "main_area");
    gtk_container_add(GTK_CONTAINER(main_window), main_area);

    build_chat_screen();              // Build the chat screen within the main area
    gtk_widget_show_all(main_window); // Show all components of the main window
}
