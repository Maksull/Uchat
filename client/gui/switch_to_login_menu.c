#include "../inc/client.h"

// Function to switch to the login menu
void switch_to_login_menu(GtkWidget *widget, gpointer data)
{
    if (widget) { }
    (void)data;
    GtkWidget *signup_menu = get_widget_by_name_r(main_window, "signup_menu"); // Find the signup menu widget within the main window
    gtk_widget_destroy(GTK_WIDGET(signup_menu));                               // Destroy the signup menu widget if found
    build_login_menu();                                                        // Build the login menu
}
