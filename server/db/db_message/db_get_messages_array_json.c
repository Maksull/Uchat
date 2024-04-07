#include "../../inc/server.h"

// Get messages array in JSON format
cJSON *db_get_messages_array_json(int chat_id)
{

    cJSON *chats_json = cJSON_CreateArray();
    sqlite3 *db = open_db();
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "SELECT messages.id, messages.user_id, users.username, users.avatar_color, messages.chat_id, messages.text, messages.date "
                           "FROM `messages` INNER JOIN `users` ON users.id = messages.user_id "
                           "WHERE messages.chat_id = ?",
                       -1, &stmt, NULL);

    sqlite3_bind_int64(stmt, 1, chat_id);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {

        cJSON_AddItemToArray(chats_json, sql_to_json_message(stmt));
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return chats_json;
}
