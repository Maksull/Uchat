#include "../inc/server.h"

cJSON *db_get_search_chats(const cJSON *chat_info, t_server_utils *utils)
{
    cJSON *search_pattern = cJSON_GetObjectItemCaseSensitive(chat_info, "search_pattern");
    if (!cJSON_IsString(search_pattern))
    {
        return NULL;
    }

    cJSON *chats_json = cJSON_CreateArray();
    sqlite3 *db = open_database();
    sqlite3_stmt *stmt;
    char *search_str = mx_strnew(mx_strlen(search_pattern->valuestring) + 4);
    mx_strcat(search_str, "%%");
    mx_strcat(search_str, search_pattern->valuestring);
    mx_strcat(search_str, "%%");
    sqlite3_prepare_v2(db, "SELECT chats.id, chats.name, chats.avatar_color FROM chats "
                           "WHERE chats.name LIKE ? "
                           "AND chats.id NOT IN (SELECT `chat_id` FROM `members` WHERE `user_id` = ?) "
                           "ORDER BY chats.date DESC ",
                       -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, search_str, -1, NULL);
    sqlite3_bind_int64(stmt, 2, utils->user->user_id);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        cJSON_AddItemToArray(chats_json, stmt_to_chat_json(stmt, true));
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    mx_strdel(&search_str);

    return chats_json;
}
