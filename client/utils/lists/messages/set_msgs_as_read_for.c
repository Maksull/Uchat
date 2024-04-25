#include "../../../inc/client.h"

// Set new messages in a chat as read
void set_msgs_as_read_for(t_chat *chat)
{
	// Check if the chat or new_messages list is NULL
	if (!chat || !chat->new_messages)
	{
		return;
	}
	
	// Iterate through the new_messages list
	t_msg *new_msg = chat->new_messages;
	while (new_msg)
	{
		// Add the new message to the messages list
		mx_msg_dfl_push_back(&chat->messages,
							 new_msg->message_id, new_msg->sender_id, new_msg->sender_name,
							 new_msg->chat_id, new_msg->text, new_msg->date_str, new_msg->avatar_color);
		// Get the added message
		t_msg *msg_to_add = mx_get_last_msg_node(chat->messages);
		// Decrement the new_msg_count if greater than or equal to 1
		if (chat->new_msg_count >= 1)
		{
			chat->new_msg_count -= 1;
		}
		// Update the chat field if it's the first message
		if (mx_msg_list_size(chat->messages) == 1)
		{
			update_chat_field();
		}
		else
		{
			add_message(msg_to_add);
		}
		// Move to the next new message
		new_msg = new_msg->next;
	}
	// Clear the new_messages list
	mx_clear_msg_list(&chat->new_messages);
}
