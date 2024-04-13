#include "../../inc/server.h"

// Function to search chats based on a search pattern in the database
static cJSON *search_chats_in_db(const char *search_pattern, int user_id, sqlite3 *db)
{
    cJSON *chats_json = cJSON_CreateArray();

    char *search_str = mx_strnew(mx_strlen(search_pattern) + 4);
    mx_strcat(search_str, "%%");
    mx_strcat(search_str, search_pattern);
    mx_strcat(search_str, "%%");

    sqlite3_stmt *sql_stmt;
    sqlite3_prepare_v2(db, "SELECT chats.id, chats.name, chats.avatar_color FROM chats "
                           "WHERE chats.name LIKE ? "
                           "AND chats.id NOT IN (SELECT `chat_id` FROM `members` WHERE `user_id` = ?) "
                           "ORDER BY chats.date DESC ",
                       -1, &sql_stmt, NULL);
    sqlite3_bind_text(sql_stmt, 1, search_str, -1, NULL);
    sqlite3_bind_int64(sql_stmt, 2, user_id);

    while (sqlite3_step(sql_stmt) == SQLITE_ROW)
    {
        cJSON_AddItemToArray(chats_json, sql_to_json_chat(sql_stmt, true));
    }

    sqlite3_finalize(sql_stmt);
    mx_strdel(&search_str);

    return chats_json;
}

// Original function refactored
cJSON *db_get_search_chats(const cJSON *chat_info, t_server_utils *utils)
{
    cJSON *search_pattern = cJSON_GetObjectItemCaseSensitive(chat_info, "search_pattern");

    if (!cJSON_IsString(search_pattern))
    {
        return NULL;
    }

    sqlite3 *db = open_db();
    cJSON *chats_json = search_chats_in_db(search_pattern->valuestring, utils->user->user_id, db);
    sqlite3_close(db);

    return chats_json;
}
