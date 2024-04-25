#include "../../inc/client.h"

// Function to build chat screen
void build_chat_screen()
{
    GtkWidget *main_area = get_widget_by_name_r(main_window, "main_area"); // Retrieve the main_area widget from the main window
    GtkWidget *grid = gtk_grid_new();                                      // Create a new grid widget to serve as the layout for the chat screen
    // Set properties for row spacing and homogeneity within the grid
    gtk_grid_set_row_spacing(GTK_GRID(grid), 3);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_container_add(GTK_CONTAINER(main_area), grid); // Add the grid widget to the main_area container

    build_leftbar(grid);  // Build and add the left sidebar to the grid layout
    build_rightbar(grid); // Build and add the right sidebar to the grid layout

    update_chatlist(); // Update the chat list

    gtk_widget_show_all(grid); // Display the grid widget and its children
}
