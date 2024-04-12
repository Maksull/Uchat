#include "../../inc/server.h"

// Function to validate JSON object for message editing
static int validate_message_edit_json(const cJSON *msg_json)
{
    const cJSON *message_id = cJSON_GetObjectItem(msg_json, "id");
    const cJSON *chat_id = cJSON_GetObjectItem(msg_json, "chat_id");
    const cJSON *new_text = cJSON_GetObjectItemCaseSensitive(msg_json, "text");

    if (!cJSON_IsNumber(message_id) || !cJSON_IsNumber(chat_id) || !cJSON_IsString(new_text))
    {
        return 0; // JSON validation failed
    }

    // Check if the new message text length is within the valid range
    if (!is_strlen_valid(new_text->valuestring, MIN_MSG_INPUT_LEN, MAX_MSG_INPUT_LEN))
    {
        return 0; // Invalid message length
    }

    return 1; // JSON validation succeeded
}

// Function to create SQL query for updating message text
static void create_edit_message_query(int message_id, int user_id, int chat_id, const char *new_text, char *query)
{
    sprintf(query, "UPDATE `messages` SET `text` = '%s' WHERE `id` = '%d' AND `user_id` = '%d' AND `chat_id` = '%d'",
            new_text, message_id, user_id, chat_id);
}

// Function to edit a message in the database
t_response_code db_edit_message(const cJSON *msg_json, t_server_utils *utils)
{
    const cJSON *message_id = cJSON_GetObjectItem(msg_json, "id");
    const cJSON *chat_id = cJSON_GetObjectItem(msg_json, "chat_id");
    const cJSON *new_text = cJSON_GetObjectItemCaseSensitive(msg_json, "text");

    char query[QUERY_LEN];

    // Check JSON validity
    if (!validate_message_edit_json(msg_json))
    {
        return R_JSON_FAILURE; // JSON validation failed
    }

    create_edit_message_query(message_id->valueint, utils->user->user_id, chat_id->valueint, new_text->valuestring, query);

    // Open the database connection
    sqlite3 *db = open_db();
    if (db == NULL)
    {
        return R_DB_FAILURE; // Failed to open database
    }

    // Prepare the SQL statement
    sqlite3_stmt *sql_stmt;
    if (sqlite3_prepare_v2(db, query, -1, &sql_stmt, NULL) != SQLITE_OK)
    {
        sqlite3_close(db);
        return R_DB_FAILURE; // Failed to prepare SQL statement
    }

    // Bind the new message text to the SQL statement
    if (sqlite3_bind_text(sql_stmt, 1, new_text->valuestring, -1, NULL) != SQLITE_OK)
    {
        sqlite3_finalize(sql_stmt);
        sqlite3_close(db);
        return R_DB_FAILURE; // Failed to bind parameter
    }

    // Execute the SQL statement to update the message text
    if (sqlite3_step(sql_stmt) != SQLITE_DONE)
    {
        sqlite3_finalize(sql_stmt);
        sqlite3_close(db);
        return R_DB_FAILURE; // Failed to execute SQL statement
    }

    // Finalize the SQL statement and close the database connection
    sqlite3_finalize(sql_stmt);
    sqlite3_close(db);

    return R_SUCCESS; // Message editing successful
}
