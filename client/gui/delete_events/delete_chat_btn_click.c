#include "../../inc/client.h"

// Function to update chat list and destroy chat window
static void update_and_destroy_chat(GtkWidget *widget) {
    // Set the current chat pointer to NULL and update the chat list
    utils->current_chat = NULL;
    update_chatlist();

    // Destroy the top-level window containing the chat
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget);
    gtk_widget_destroy(toplevel);
}


// Function to handle delete chat button click
void delete_chat_btn_click(GtkWidget *widget, gpointer data)
{
    int response_code = handle_delete_chat_req(utils->current_chat->name); // Send a request to delete the current chat and get the response code

    // If the deletion is successful, update the chat list and destroy the window
    if (response_code == R_SUCCESS)
    {
        // Call the function to update chat list and destroy chat window
        update_and_destroy_chat(widget);
    }
    (void)data;
}
