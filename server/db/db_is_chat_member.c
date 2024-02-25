#include "../inc/server.h"

bool db_is_chat_member(int user_id, int chat_id)
{
    char query[QUERY_LEN];
    sprintf(query,
            "SELECT EXISTS (SELECT `id` FROM `members` WHERE `user_id` = '%d' AND `chat_id` = '%d')",
            user_id, chat_id);

    sqlite3 *db = open_database();
    sqlite3_stmt *stmt = db_execute_stmt_for(query, db);

    int is_chat_member = sqlite3_column_int64(stmt, 0);
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return is_chat_member == 1;
}
