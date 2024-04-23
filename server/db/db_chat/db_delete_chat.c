#include "../../inc/server.h"
// Function to delete a chat from the database
static t_response_code delete_chat_from_db(const char *chat_name)
{
    // Define a buffer to hold the SQL query.
    char query[QUERY_LEN];
    // Construct the SQL query to delete the chat with the specified name from the 'chats' table.
    sprintf(query, "DELETE FROM `chats` WHERE `name` = '%s'", chat_name);

    // Execute the SQL query to delete the chat from the database.
    if (db_execute_query(query) != 0)
    {
        // If the deletion operation fails, return the appropriate response code.
        return R_DB_FAILURE;
    }

    // If the deletion operation is successful, return the success response code.
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
