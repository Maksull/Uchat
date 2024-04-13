#include "../../inc/server.h"

// Function to check if a chat exists in the database
static bool chat_exists_in_db(int chat_id, sqlite3 *db)
{
    char query[QUERY_LEN];
    sprintf(query, "SELECT EXISTS (SELECT `id` FROM `chats` WHERE `id` = '%d')", chat_id);

    sqlite3_stmt *sql_stmt = db_execute_sql_stmt(query, db);
    int chat_exists = sqlite3_column_int64(sql_stmt, 0);
    sqlite3_finalize(sql_stmt);

    return chat_exists == 1;
}

// Original function refactored
bool db_chat_exists(int chat_id)
{
    sqlite3 *db = open_db();
    bool exists = chat_exists_in_db(chat_id, db);
    sqlite3_close(db);

    return exists;
}
