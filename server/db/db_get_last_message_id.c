#include "../inc/server.h"

// Function to retrieve the ID of the last message in a chat from the database
t_response_code db_get_last_message_id(const cJSON *chat_info, int *last_msg_id)
{
    // Extract chat_id from the JSON object
    const cJSON *chat_id = cJSON_GetObjectItemCaseSensitive(chat_info, "chat_id");

    // Check if chat_id is a number
    if (!cJSON_IsNumber(chat_id))
    {
        return R_JSON_FAILURE;
    }

    // Check if the chat exists in the database
    if (!db_chat_exists(chat_id->valueint))
    {
        return R_CHAT_NOENT;
    }

    // Construct the SQL query to retrieve the ID of the last message in the chat
    char query[QUERY_LEN];
    sprintf(query, "SELECT id FROM `messages` WHERE chat_id = %d ORDER BY id DESC LIMIT 1",
            chat_id->valueint);

    sqlite3 *db = open_database();
    // Execute the SQL query and get the result
    sqlite3_stmt *stmt = db_execute_stmt_for(query, db);
    *last_msg_id = sqlite3_column_int64(stmt, 0);
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return R_SUCCESS;
}
