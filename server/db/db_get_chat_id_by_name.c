#include "../inc/server.h"

int db_get_chat_id_by_name(const char *chat_name)
{
    sqlite3 *db = open_database();
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "SELECT `id` FROM `chats` WHERE `name` = ?", -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, chat_name, -1, NULL);

    int chat_id = -1;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        chat_id = sqlite3_column_int64(stmt, 0);
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return chat_id;
}