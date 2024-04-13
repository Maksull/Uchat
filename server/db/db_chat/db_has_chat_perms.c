#include "../../inc/server.h"

// Function to check if a user has specific permissions for a chat in the database
static bool user_has_chat_perms_in_db(int user_id, int chat_id, t_member_type perms, sqlite3 *db)
{
    char query[QUERY_LEN];
    sprintf(query, "SELECT `permissions` FROM `members` WHERE `user_id` = '%d' AND `chat_id` = '%d'", user_id, chat_id);

    sqlite3_stmt *sql_stmt = db_execute_sql_stmt(query, db);
    int chat_perms = sqlite3_column_int64(sql_stmt, 0);
    sqlite3_finalize(sql_stmt);

    return (t_member_type)chat_perms == perms;
}

// Original function refactored
bool db_has_chat_perms(int user_id, int chat_id, t_member_type perms)
{
    sqlite3 *db = open_db();
    bool has_perms = user_has_chat_perms_in_db(user_id, chat_id, perms, db);
    sqlite3_close(db);

    return has_perms;
}
