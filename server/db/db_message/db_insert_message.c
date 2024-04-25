#include "../../inc/server.h"

// Function to validate message JSON object
static int validate_message_json(const cJSON *msg_json)
{
    const cJSON *user_id = cJSON_GetObjectItem(msg_json, "user_id");
    const cJSON *chat_id = cJSON_GetObjectItem(msg_json, "chat_id");
    const cJSON *user_name = cJSON_GetObjectItemCaseSensitive(msg_json, "user_name");
    const cJSON *message = cJSON_GetObjectItemCaseSensitive(msg_json, "text");
    const cJSON *date = cJSON_GetObjectItemCaseSensitive(msg_json, "date");

    if (!cJSON_IsNumber(user_id) || !cJSON_IsNumber(chat_id) ||
        !cJSON_IsString(user_name) || !cJSON_IsString(message) || !cJSON_IsNumber(date))
    {
        return 0; // Invalid message JSON
    }

    return 1; // JSON validation succeeded
}

// Function to insert message into the database
static t_response_code insert_message_into_db(const cJSON *msg_json, int *message_id)
{
    const cJSON *user_id = cJSON_GetObjectItem(msg_json, "user_id");
    const cJSON *chat_id = cJSON_GetObjectItem(msg_json, "chat_id");
    const cJSON *message = cJSON_GetObjectItemCaseSensitive(msg_json, "text");
    const cJSON *date = cJSON_GetObjectItemCaseSensitive(msg_json, "date");

    char query[QUERY_LEN];
    sprintf(query, "INSERT INTO `messages` (`user_id`, `chat_id`, `text`, `date`) VALUES('%d', '%d', ?, '%d')",
            user_id->valueint, chat_id->valueint, date->valueint);

    sqlite3 *db = open_db();
    if (db == NULL)
    {
        return R_DB_FAILURE; // Failed to open database
    }

    sqlite3_stmt *sql_stmt;
    if (sqlite3_prepare_v2(db, query, -1, &sql_stmt, NULL) != SQLITE_OK)
    {
        sqlite3_close(db);

        return R_DB_FAILURE; // Failed to prepare SQL statement
    }

    if (sqlite3_bind_text(sql_stmt, 1, message->valuestring, -1, NULL) != SQLITE_OK)
    {
        sqlite3_finalize(sql_stmt);
        sqlite3_close(db);

        return R_DB_FAILURE; // Failed to bind parameter
    }

    if (sqlite3_step(sql_stmt) != SQLITE_DONE)
    {
        sqlite3_finalize(sql_stmt);
        sqlite3_close(db);

        return R_DB_FAILURE; // Failed to execute SQL statement
    }

    sprintf(query, "SELECT id FROM `messages` WHERE `user_id` = '%d' AND `chat_id` = '%d' "
                   "ORDER BY `id` DESC LIMIT 1",
            user_id->valueint, chat_id->valueint);

    if (sqlite3_prepare_v2(db, query, -1, &sql_stmt, NULL) != SQLITE_OK)
    {
        sqlite3_finalize(sql_stmt);
        sqlite3_close(db);

        return R_DB_FAILURE; // Failed to prepare SQL statement for message ID retrieval
    }

    if (sqlite3_step(sql_stmt) != SQLITE_ROW)
    {
        sqlite3_finalize(sql_stmt);
        sqlite3_close(db);

        return R_DB_FAILURE; // Failed to retrieve message ID
    }

    *message_id = sqlite3_column_int64(sql_stmt, 0);

    sqlite3_finalize(sql_stmt);
    sqlite3_close(db);

    return R_SUCCESS; // Message successfully inserted
}

// Function to insert a message into the database
t_response_code db_insert_message(const cJSON *msg_json, int *message_id)
{
    if (!validate_message_json(msg_json))
    {
        return R_JSON_FAILURE; // Invalid message JSON
    }

    return insert_message_into_db(msg_json, message_id);
}
