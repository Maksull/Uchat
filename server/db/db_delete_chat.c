#include "../inc/server.h"

// Delete a chat from the database
t_response_code db_delete_chat(const char *chat_name, int chat_id)
{
    // Check if the chat exists
    if (!db_chat_exists(chat_id))
    {
        // If the chat does not exist, return chat not found error code
        return R_CHAT_NOENT;
    }

    // Create SQL query to delete the chat
    char query[QUERY_LEN];
    sprintf(query, "DELETE FROM `chats` WHERE `name` = '%s'", chat_name);

    // Execute the SQL query
    if (db_execute_query(query) != 0)
    {
        // If executing the query fails, return database failure error code
        return R_DB_FAILURE;
    }

    return R_SUCCESS;
}
