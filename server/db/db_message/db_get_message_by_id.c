#include "../../inc/server.h"

// Function to retrieve a message by its ID from the database
cJSON *db_get_message_by_id(const cJSON *msg_info)
{
    // Extract chat_id and message_id from the JSON object
    const cJSON *chat_id = cJSON_GetObjectItemCaseSensitive(msg_info, "chat_id");
    const cJSON *message_id = cJSON_GetObjectItemCaseSensitive(msg_info, "message_id");

    // Check if chat_id and message_id are numbers
    if (!cJSON_IsNumber(chat_id) || !cJSON_IsNumber(message_id))
    {
        return NULL;
    }

    sqlite3 *db = open_db();
    sqlite3_stmt *sql_stmt;

    // Prepare the SQL statement to retrieve the message from the database
    sqlite3_prepare_v2(db, "SELECT messages.id, messages.user_id, users.username, users.avatar_color, messages.chat_id, messages.text, messages.date "
                           "FROM `messages` INNER JOIN `users` ON users.id = messages.user_id "
                           "WHERE messages.chat_id = ? AND messages.id = ?",
                       -1, &sql_stmt, NULL);

    // Bind the values for chat_id and message_id to the SQL statement
    sqlite3_bind_int64(sql_stmt, 1, chat_id->valueint);
    sqlite3_bind_int64(sql_stmt, 2, message_id->valueint);

    cJSON *message_json = NULL;
    // If the SQL query returns a row, extract the message JSON
    if (sqlite3_step(sql_stmt) == SQLITE_ROW)
    {
        message_json = sql_to_json_message(sql_stmt);
    }
    sqlite3_finalize(sql_stmt);
    sqlite3_close(db);

    return message_json;
}
