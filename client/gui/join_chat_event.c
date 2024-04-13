#include "../inc/client.h"

// Function to check if the event is a single button press event
static gboolean is_single_button_press_event(GdkEventButton *event) {
    return event->type == GDK_BUTTON_PRESS && event->button == 1;
}

// Function to check if the event is a double button press event
static gboolean is_double_button_press_event(GdkEventButton *event) {
    return event->type == GDK_DOUBLE_BUTTON_PRESS && event->button == 1;
}

// Function to handle the double-click event (attempting to join chat)
static void handle_double_click_event(char *chat_name) {
    // Request to join the chat and handle the response
    int response_code = handle_join_chat_req(chat_name);
    handle_join_chat_response_code(response_code, chat_name);
}

// Function to handle join chat event
void join_chat_event(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
    char *chat_name = (char *)gtk_widget_get_name(widget); // Extract the chat name from the widget's name

    // Handle single-click event (set chat item as active)
    if (is_single_button_press_event(event)) 
    {
        set_chatlist_item_active(widget);
    }
    else if (is_double_button_press_event(event)) // Handle double-click event (attempt to join chat)
    {
        handle_double_click_event(chat_name);
    }
    (void)data;
}
