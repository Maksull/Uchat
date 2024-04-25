#include "../../inc/server.h"

// Function to extract message_id, chat_id, and new_text from the JSON object
static int extract_message_data(const cJSON *msg_json, int *message_id, int *chat_id, const char **new_text)
{
    const cJSON *id = cJSON_GetObjectItem(msg_json, "id");
    const cJSON *chat = cJSON_GetObjectItem(msg_json, "chat_id");
    const cJSON *text = cJSON_GetObjectItemCaseSensitive(msg_json, "text");

    // Check if any required fields are missing
    if (!id || !chat || !text)
    {
        return -1;
    }

    // Check if message_id is a number and new_text is a string
    if (!cJSON_IsNumber(id) || !cJSON_IsString(text))
    {
        return -1;
    }

    *message_id = id->valueint;
    *chat_id = chat->valueint;
    *new_text = text->valuestring;

    return 0;
}

// Function to update message text in the database
static t_response_code update_message_text(int message_id, int chat_id, const char *new_text, t_server_utils *utils)
{
    // Construct the SQL query to update the message text in the messages table
    char query[QUERY_LEN];
    snprintf(query, QUERY_LEN, "UPDATE `messages` SET `text` = ? WHERE `id` = '%d' AND `user_id` = '%d' AND `chat_id` = '%d'",
             message_id, utils->user->user_id, chat_id);

    // Open the database connection
    sqlite3 *db = open_db();

    // Prepare the SQL statement
    sqlite3_stmt *sql_stmt;
    sqlite3_prepare_v2(db, query, -1, &sql_stmt, NULL);

    // Bind the new message text to the SQL statement
    sqlite3_bind_text(sql_stmt, 1, new_text, -1, NULL);

    // Execute the SQL statement to update the message text
    sqlite3_step(sql_stmt);

    // Finalize the SQL statement and close the database connection
    sqlite3_finalize(sql_stmt);
    sqlite3_close(db);

    return R_SUCCESS; // Return success code if the message is successfully updated
}

t_response_code db_edit_message(const cJSON *msg_json, t_server_utils *utils)
{
    int message_id, chat_id;
    const char *new_text;

    // Extract message data from JSON object
    if (extract_message_data(msg_json, &message_id, &chat_id, &new_text) != 0)
    {
        return R_JSON_FAILURE; // Return JSON failure code if extraction fails
    }

    // Check if the new message text length is within the valid range
    if (!is_strlen_valid(new_text, MIN_MSG_INPUT_LEN, MAX_MSG_INPUT_LEN))
    {
        return R_MSG_LEN_INVALID; // Return invalid message length code if the new message length is invalid
    }

    // Update message text in the database
    return update_message_text(message_id, chat_id, new_text, utils);
}
