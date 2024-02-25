#include "../inc/server.h"

int db_get_chats_total(int user_id)
{
    char query[QUERY_LEN];
    sprintf(query, "SELECT COUNT(*) FROM chats "
                   "INNER JOIN members ON members.chat_id = chats.id "
                   "WHERE members.user_id IN (%d)",
            user_id);

    sqlite3 *db = open_database();
    sqlite3_stmt *stmt = db_execute_stmt_for(query, db);
    int chat_total = sqlite3_column_int64(stmt, 0);
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return chat_total;
}
