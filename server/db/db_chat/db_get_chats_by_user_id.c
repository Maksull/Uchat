#include "../../inc/server.h"

// Function to get chats associated with a user ID from the database
static cJSON *get_chats_by_user_id_from_db(int user_id, sqlite3 *db)
{
    cJSON *chats_json = cJSON_CreateArray();

    sqlite3_stmt *sql_stmt;
    sqlite3_prepare_v2(db, "SELECT chats.id, chats.name, chats.avatar_color, members.permissions FROM chats "
                           "INNER JOIN `members` ON members.chat_id = chats.id "
                           "WHERE chats.id IN (SELECT `chat_id` FROM `members` WHERE `user_id` = ?) AND members.user_id = ? "
                           "ORDER BY chats.date DESC ",
                       -1, &sql_stmt, NULL);
    sqlite3_bind_int64(sql_stmt, 1, user_id);
    sqlite3_bind_int64(sql_stmt, 2, user_id);

    while (sqlite3_step(sql_stmt) == SQLITE_ROW)
    {
        cJSON_AddItemToArray(chats_json, sql_to_json_chat(sql_stmt, false));
    }

    sqlite3_finalize(sql_stmt);

    return chats_json;
}

// Original function refactored
cJSON *db_get_chats_by_user_id(int user_id)
{
    sqlite3 *db = open_db();
    cJSON *chats_json = get_chats_by_user_id_from_db(user_id, db);
    sqlite3_close(db);

    return chats_json;
}
