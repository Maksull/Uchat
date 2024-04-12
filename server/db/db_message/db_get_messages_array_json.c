#include "../../inc/server.h"

// Function to prepare SQL statement for retrieving messages by chat ID
static sqlite3_stmt *prepare_messages_query(int chat_id, sqlite3 *db)
{
    sqlite3_stmt *sql_stmt;
    sqlite3_prepare_v2(db, "SELECT messages.id, messages.user_id, users.username, users.avatar_color, messages.chat_id, messages.text, messages.date "
                           "FROM `messages` INNER JOIN `users` ON users.id = messages.user_id "
                           "WHERE messages.chat_id = ?",
                       -1, &sql_stmt, NULL);
    sqlite3_bind_int64(sql_stmt, 1, chat_id);

    return sql_stmt;
}

// Function to retrieve messages array in JSON format
static cJSON *get_messages_array_json(int chat_id, sqlite3_stmt *sql_stmt)
{
    cJSON *messages_json = cJSON_CreateArray();

    while (sqlite3_step(sql_stmt) == SQLITE_ROW)
    {
        cJSON_AddItemToArray(messages_json, sql_to_json_message(sql_stmt));
    }

    return messages_json;
}

// Function to retrieve messages array in JSON format from the database by chat ID
cJSON *db_get_messages_array_json(int chat_id)
{
    sqlite3 *db = open_db();
    if (db == NULL)
    {
        return NULL; // Failed to open database
    }

    sqlite3_stmt *sql_stmt = prepare_messages_query(chat_id, db);
    if (sql_stmt == NULL)
    {
        sqlite3_close(db);
        return NULL; // Failed to prepare SQL statement
    }

    cJSON *messages_json = get_messages_array_json(chat_id, sql_stmt);

    sqlite3_finalize(sql_stmt);
    sqlite3_close(db);

    return messages_json;
}
