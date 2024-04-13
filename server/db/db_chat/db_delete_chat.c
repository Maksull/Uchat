#include "../../inc/server.h"
// Function to delete a chat from the database
static t_response_code delete_chat_from_db(const char *chat_name)
{
    char query[QUERY_LEN];
    sprintf(query, "DELETE FROM `chats` WHERE `name` = '%s'", chat_name);

    if (db_execute_query(query) != 0)
    {
        return R_DB_FAILURE;
    }

    return R_SUCCESS;
}

// Original function refactored
t_response_code db_delete_chat(const char *chat_name, int chat_id)
{
    // Check if the chat exists
    if (!db_chat_exists(chat_id))
    {
        // If the chat does not exist, return chat not found error code
        return R_CHAT_NOENT;
    }

    // Delete the chat from the database
    return delete_chat_from_db(chat_name);
}
