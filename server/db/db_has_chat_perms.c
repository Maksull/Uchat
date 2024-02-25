#include "../inc/server.h"

bool db_has_chat_perms(int user_id, int chat_id, t_member_type perms)
{
    char query[QUERY_LEN];
    sprintf(query, "SELECT `permissions` FROM `members` WHERE `user_id` = '%d' AND `chat_id` = '%d'", user_id, chat_id);

    sqlite3 *db = open_database();
    sqlite3_stmt *stmt = db_execute_stmt_for(query, db);

    int chat_perms = sqlite3_column_int64(stmt, 0);
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return (t_member_type)chat_perms == perms;
}
