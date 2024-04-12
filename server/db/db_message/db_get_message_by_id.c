#include "../../inc/server.h"

// Function to prepare SQL statement for retrieving a message by its ID
static sqlite3_stmt *prepare_message_query(int chat_id, int message_id, sqlite3 *db)
{
    sqlite3_stmt *sql_stmt;
    sqlite3_prepare_v2(db, "SELECT messages.id, messages.user_id, users.username, users.avatar_color, messages.chat_id, messages.text, messages.date "
                           "FROM `messages` INNER JOIN `users` ON users.id = messages.user_id "
                           "WHERE messages.chat_id = ? AND messages.id = ?",
                       -1, &sql_stmt, NULL);
    sqlite3_bind_int64(sql_stmt, 1, chat_id);
    sqlite3_bind_int64(sql_stmt, 2, message_id);
    
    return sql_stmt;
}

// Function to retrieve a message JSON object from SQL result
static cJSON *extract_message_json(sqlite3_stmt *sql_stmt)
{
    cJSON *message_json = NULL;
    if (sqlite3_step(sql_stmt) == SQLITE_ROW)
    {
        message_json = sql_to_json_message(sql_stmt);
    }

    return message_json;
}

// Function to retrieve a message by its ID from the database
cJSON *db_get_message_by_id(const cJSON *msg_info)
{
    const cJSON *chat_id = cJSON_GetObjectItemCaseSensitive(msg_info, "chat_id");
    const cJSON *message_id = cJSON_GetObjectItemCaseSensitive(msg_info, "message_id");

    if (!cJSON_IsNumber(chat_id) || !cJSON_IsNumber(message_id))
    {
        return NULL; // Invalid input parameters
    }

    sqlite3 *db = open_db();
    if (db == NULL)
    {
        return NULL; // Failed to open database
    }

    sqlite3_stmt *sql_stmt = prepare_message_query(chat_id->valueint, message_id->valueint, db);
    if (sql_stmt == NULL)
    {
        sqlite3_close(db);
        return NULL; // Failed to prepare SQL statement
    }

    cJSON *message_json = extract_message_json(sql_stmt);

    sqlite3_finalize(sql_stmt);
    sqlite3_close(db);

    return message_json;
}
