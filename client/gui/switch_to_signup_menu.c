#include "../inc/client.h"

// Function to switch to the signup menu
void switch_to_signup_menu(GtkWidget *widget, gpointer data)
{
    if (widget) { }
    (void)data;
    GtkWidget *login_menu = get_widget_by_name_r(main_window, "login_menu"); // Find the login menu widget within the main window
    gtk_widget_destroy(GTK_WIDGET(login_menu)); // Destroy the login menu widget if found
    build_signup_menu(); // Build the signup menu
}
