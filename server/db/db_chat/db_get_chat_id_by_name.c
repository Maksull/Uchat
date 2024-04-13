#include "../../inc/server.h"

// Function to get the chat ID by its name from the database
static int get_chat_id_by_name_from_db(const char *chat_name, sqlite3 *db)
{
    sqlite3_stmt *sql_stmt;
    sqlite3_prepare_v2(db, "SELECT `id` FROM `chats` WHERE `name` = ?", -1, &sql_stmt, NULL);
    sqlite3_bind_text(sql_stmt, 1, chat_name, -1, NULL);

    int chat_id = -1;

    if (sqlite3_step(sql_stmt) == SQLITE_ROW)
    {
        chat_id = sqlite3_column_int64(sql_stmt, 0);
    }

    sqlite3_finalize(sql_stmt);

    return chat_id;
}

// Original function refactored
int db_get_chat_id_by_name(const char *chat_name)
{
    sqlite3 *db = open_db();
    int chat_id = get_chat_id_by_name_from_db(chat_name, db);
    sqlite3_close(db);

    return chat_id;
}
