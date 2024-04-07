#include "../../inc/server.h"

// Function to insert a message into the database
t_response_code db_insert_message(const cJSON *msg_json, int *message_id)
{
    // Extract necessary fields from the JSON object
    const cJSON *user_id = cJSON_GetObjectItem(msg_json, "user_id");
    const cJSON *chat_id = cJSON_GetObjectItem(msg_json, "chat_id");
    const cJSON *user_name = cJSON_GetObjectItemCaseSensitive(msg_json, "user_name");
    const cJSON *message = cJSON_GetObjectItemCaseSensitive(msg_json, "text");
    const cJSON *date = cJSON_GetObjectItemCaseSensitive(msg_json, "date");

    // Check if all required fields are present and of the correct type
    if (!cJSON_IsNumber(user_id) || !cJSON_IsNumber(chat_id) ||
        !cJSON_IsString(user_name) || !cJSON_IsString(message) || !cJSON_IsNumber(date))
    {
        return R_JSON_FAILURE;
    }

    // Check if the chat exists in the database
    if (!db_chat_exists(chat_id->valueint))
    {
        return R_CHAT_NOENT;
    }

    // Check if the message text length is within the valid range
    if (!is_strlen_valid(message->valuestring, MIN_MSG_INPUT_LEN, MAX_MSG_INPUT_LEN))
    {
        return R_MSG_LEN_INVALID;
    }

    // Construct the SQL query to insert the message into the messages table
    char query[QUERY_LEN];
    sprintf(query, "INSERT INTO `messages` (`user_id`, `chat_id`, `text`, `date`) VALUES('%d', '%d', ?, '%d')",
            user_id->valueint, chat_id->valueint, date->valueint);

    // Open the database connection
    sqlite3 *db = open_db();

    // Prepare the SQL statement
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, query, -1, &stmt, NULL);

    // Bind the message text to the SQL statement
    sqlite3_bind_text(stmt, 1, message->valuestring, -1, NULL);
    sqlite3_step(stmt);
    sqlite3_reset(stmt);
    bzero(query, sizeof(query));

    // Construct a query to retrieve the ID of the last inserted message
    sprintf(query, "SELECT id FROM `messages` WHERE `user_id` = '%d' AND `chat_id` = '%d' "
                   "ORDER BY `id` DESC LIMIT 1",
            user_id->valueint, chat_id->valueint);

    // Prepare and execute the query to retrieve the message ID
    sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    sqlite3_step(stmt);

    // Store the retrieved message ID
    *message_id = sqlite3_column_int64(stmt, 0);

    // Finalize the SQL statement and close the database connection
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return R_SUCCESS; // Return success code if the message is successfully inserted
}
