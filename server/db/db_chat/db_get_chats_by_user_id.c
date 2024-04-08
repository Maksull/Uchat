#include "../../inc/server.h"

// Get chats associated with a user ID from the database
cJSON *db_get_chats_by_user_id(int user_id)
{
    cJSON *chats_json = cJSON_CreateArray();

    sqlite3 *db = open_db(); // Open the database connection

    // Prepare SQL statement to select chats by user ID
    sqlite3_stmt *sql_stmt;
    sqlite3_prepare_v2(db, "SELECT chats.id, chats.name, chats.avatar_color, members.permissions FROM chats "
                           "INNER JOIN `members` ON members.chat_id = chats.id "
                           "WHERE chats.id IN (SELECT `chat_id` FROM `members` WHERE `user_id` = ?) AND members.user_id = ? "
                           "ORDER BY chats.date DESC ",
                       -1, &sql_stmt, NULL);
    sqlite3_bind_int64(sql_stmt, 1, user_id);
    sqlite3_bind_int64(sql_stmt, 2, user_id);

    // Iterate over the result set and add each chat to the JSON array
    while (sqlite3_step(sql_stmt) == SQLITE_ROW)
    {
        // Convert the current row to a JSON object and add it to the JSON array
        cJSON_AddItemToArray(chats_json, sql_to_json_chat(sql_stmt, false));
    }

    sqlite3_finalize(sql_stmt);
    sqlite3_close(db);

    // Return the JSON array containing the chats
    return chats_json;
}
