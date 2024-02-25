#include "../inc/server.h"

bool db_chat_exists(int chat_id)
{
    char query[QUERY_LEN];
    sprintf(query, "SELECT EXISTS (SELECT `id` FROM `chats` WHERE `id` = '%d')", chat_id);

    sqlite3 *db = open_database();
    sqlite3_stmt *stmt = db_execute_stmt_for(query, db);

    int chat_exists = sqlite3_column_int64(stmt, 0);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    
    return chat_exists == 1;
}