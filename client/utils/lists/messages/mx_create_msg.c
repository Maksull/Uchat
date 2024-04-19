#include "../../../inc/client.h"

// Function to initialize a message node
static void initialize_msg_node(t_msg *new_node, int msg_id, int user_id, const char *user_name, int chat_id, const char *text, const char *date_str, t_avatar_color color)
{
    // Assign values to the fields of the message node
    new_node->message_id = msg_id;
    new_node->chat_id = chat_id;
    new_node->sender_id = user_id;
    new_node->sender_name = mx_strdup(user_name); // Duplicate the username string
    new_node->text = mx_strdup(text); // Duplicate the message text string
    new_node->date_str = mx_strdup(date_str); // Duplicate the date string
    new_node->avatar_color = color;
    new_node->avatar_path = NULL;
    new_node->next = NULL;
}

// Function to create message
t_msg *mx_create_msg(int msg_id, int user_id, const char *user_name, int chat_id, const char *text, const char *date_str, t_avatar_color color)
{
    t_msg *new_node = malloc(sizeof(t_msg)); // Allocate memory for the new message object

    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }

    // Initialize the message node
    initialize_msg_node(new_node, msg_id, user_id, user_name, chat_id, text, date_str, color);

    return new_node; // Return a pointer to the newly created message object
}
