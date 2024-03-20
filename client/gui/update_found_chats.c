#include "../inc/client.h"

// Function to handle update found chats
static void update_found_chats(char *search_str)
{
    t_chat *chat_list = handle_search_chats_request(search_str); // Get list of chats
    build_found_chats(chat_list); // Build chats
}
