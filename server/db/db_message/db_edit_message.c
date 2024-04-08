#include "../../inc/server.h"

// Function to edit a message in the database
t_response_code db_edit_message(const cJSON *msg_json, t_server_utils *utils)
{
    // Extract message_id, chat_id, and new_text from the JSON object
    const cJSON *message_id = cJSON_GetObjectItem(msg_json, "id");
    const cJSON *chat_id = cJSON_GetObjectItem(msg_json, "chat_id");
    const cJSON *new_text = cJSON_GetObjectItemCaseSensitive(msg_json, "text");

    // Check if message_id is a number and new_text is a string
    if (!cJSON_IsNumber(message_id) || !cJSON_IsString(new_text))
    {
        return R_JSON_FAILURE; // Return JSON failure code if message_id is not a number or new_text is not a string
    }

    // Check if the new message text length is within the valid range
    if (!is_strlen_valid(new_text->valuestring, MIN_MSG_INPUT_LEN, MAX_MSG_INPUT_LEN))
    {
        return R_MSG_LEN_INVALID; // Return invalid message length code if the new message length is invalid
    }

    // Construct the SQL query to update the message text in the messages table
    char query[QUERY_LEN];
    sprintf(query, "UPDATE `messages` SET `text` = ? WHERE `id` = '%d' AND `user_id` = '%d' AND `chat_id` = '%d'",
            message_id->valueint, utils->user->user_id, chat_id->valueint);

    // Open the database connection
    sqlite3 *db = open_db();

    // Prepare the SQL statement
    sqlite3_stmt *sql_stmt;
    sqlite3_prepare_v2(db, query, -1, &sql_stmt, NULL);

    // Bind the new message text to the SQL statement
    sqlite3_bind_text(sql_stmt, 1, new_text->valuestring, -1, NULL);

    // Execute the SQL statement to update the message text
    sqlite3_step(sql_stmt);

    // Finalize the SQL statement and close the database connection
    sqlite3_finalize(sql_stmt);
    sqlite3_close(db);

    return R_SUCCESS; // Return success code if the message is successfully updated
}
