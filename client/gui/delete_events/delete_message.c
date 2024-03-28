#include "../../inc/client.h"

// Function to handle delete message
void delete_message(GtkWidget *widget, GdkEventButton *event, t_msg *message)
{
    if (widget) { }
    (void)event;

    handle_delete_msg_request(message->message_id); // Send delete request
    update_chat_field();                            // Update chat field
}
