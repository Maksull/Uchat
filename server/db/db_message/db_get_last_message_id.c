#include "../../inc/server.h"

// Function to construct SQL query for retrieving last message ID
static void construct_last_message_query(int chat_id, char *query)
{
    sprintf(query, "SELECT id FROM `messages` WHERE chat_id = %d ORDER BY id DESC LIMIT 1", chat_id);
}

// Function to execute SQL query and retrieve last message ID
static int execute_last_message_query(int chat_id, int *last_msg_id)
{
    char query[QUERY_LEN];
    construct_last_message_query(chat_id, query);

    sqlite3 *db = open_db();
    if (db == NULL)
    {
        return R_DB_FAILURE; // Failed to open database
    }

    sqlite3_stmt *sql_stmt = db_execute_sql_stmt(query, db);
    if (sql_stmt == NULL)
    {
        sqlite3_close(db);
        return R_DB_FAILURE; // Failed to execute SQL statement
    }

    *last_msg_id = sqlite3_column_int64(sql_stmt, 0);
    sqlite3_finalize(sql_stmt);
    sqlite3_close(db);

    return R_SUCCESS; // Successfully retrieved last message ID
}

// Function to validate chat JSON object
static int validate_chat_json(const cJSON *chat_info)
{
    const cJSON *chat_id = cJSON_GetObjectItemCaseSensitive(chat_info, "chat_id");
    if (!cJSON_IsNumber(chat_id))
    {
        return 0; // Chat ID is not a number
    }
    
    return 1; // JSON validation succeeded
}

// Function to retrieve the ID of the last message in a chat from the database
t_response_code db_get_last_message_id(const cJSON *chat_info, int *last_msg_id)
{
    if (!validate_chat_json(chat_info))
    {
        return R_JSON_FAILURE; // JSON validation failed
    }

    const cJSON *chat_id = cJSON_GetObjectItemCaseSensitive(chat_info, "chat_id");

    if (!db_chat_exists(chat_id->valueint))
    {
        return R_CHAT_NOENT; // Chat doesn't exist
    }

    return execute_last_message_query(chat_id->valueint, last_msg_id);
}
