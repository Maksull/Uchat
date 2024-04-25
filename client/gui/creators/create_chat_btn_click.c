#include "../../inc/client.h"

// Function to create and build chat menu
// Function to retrieve the chat name field and notification label from the top-level window
static void get_chat_name_widgets(GtkWidget *widget, GtkWidget **chat_name_field, GtkWidget **chat_name_notify_label)
{
    GtkWidget *toplevel = gtk_widget_get_toplevel(widget); // Get the top-level window containing the widget
    *chat_name_field = get_widget_by_name_r(toplevel, "chat_name_field");
    *chat_name_notify_label = get_widget_by_name_r(toplevel, "chat_name_notify_label");
}

// Function to handle the click event of the create chat button
static void handle_create_chat_button_click(GtkWidget *chat_name_field, GtkWidget *chat_name_notify_label)
{
    // Validate the chat name field
    if (!validate_name_field(chat_name_field, chat_name_notify_label))
    {
        return;
    }

    char *group_name = (char *)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(chat_name_field))); // Retrieve the group name from the chat name field

    int response_code = handle_create_chat_req(group_name);                                   // Send a request to create a chat with the specified name
    handle_create_chat_response_code(response_code, chat_name_field, chat_name_notify_label); // Handle the response code from the server
}

// Function to handle the click event of the create chat button
void create_chat_btn_click(GtkWidget *widget, gpointer data)
{
    (void)data;
    GtkWidget *chat_name_field, *chat_name_notify_label;
    get_chat_name_widgets(widget, &chat_name_field, &chat_name_notify_label);
    handle_create_chat_button_click(chat_name_field, chat_name_notify_label);
}
