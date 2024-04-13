#include "../../inc/server.h"

// Function to get the total number of chats associated with a user ID from the database
static int get_chats_total_from_db(int user_id, sqlite3 *db)
{
    char query[QUERY_LEN];
    sprintf(query, "SELECT COUNT(*) FROM chats "
                   "INNER JOIN members ON members.chat_id = chats.id "
                   "WHERE members.user_id = %d",
            user_id);

    sqlite3_stmt *sql_stmt = db_execute_sql_stmt(query, db);
    int chat_total = sqlite3_column_int64(sql_stmt, 0);
    sqlite3_finalize(sql_stmt);

    return chat_total;
}

// Original function refactored
int db_get_chats_total(int user_id)
{
    sqlite3 *db = open_db();
    int chat_total = get_chats_total_from_db(user_id, db);
    sqlite3_close(db);

    return chat_total;
}
