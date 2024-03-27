#include "../../inc/client.h"

// Function to handle change avatar button click
void change_avatar_btn_click(GtkWidget *widget, gpointer data)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget); // Get the top-level window containing the widget
    (void)data;

    // Code below is commented out because it's intended to handle avatar change logic
    // Uncomment and modify as necessary when implementing avatar change functionality
    // GtkWidget *path_field = get_widget_by_name_r(toplevel, "path_field");
    // GtkWidget *path_notify_label = get_widget_by_name_r(toplevel, "path_notify_label");

    // char *new_avatar = (char*)gtk_entry_get_text(GTK_ENTRY(path_field)); // Get the new avatar file path entered by the user

    // handle_update_user_image(new_avatar); // Handle the process of updating the user's avatar image
    // usleep(4000000); / Wait for a certain amount of time (4s) for the update process to complete
    // handle_get_user_image(utils->current_user->user_id, &utils->current_user->avatar_path); // Retrieve the updated user's avatar information

    gtk_widget_destroy(toplevel); // Destroy the top-level window
}
