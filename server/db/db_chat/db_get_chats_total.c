#include "../../inc/server.h"

// Get the total number of chats associated with a user ID from the database
int db_get_chats_total(int user_id)
{
    // Create SQL query to count the total number of chats for a user
    char query[QUERY_LEN]; // Buffer to hold SQL query
    sprintf(query, "SELECT COUNT(*) FROM chats "
                   "INNER JOIN members ON members.chat_id = chats.id "
                   "WHERE members.user_id IN (%d)",
            user_id); // Format SQL query

    sqlite3 *db = open_db(); // Open the database connection

    // Execute the SQL query and retrieve the result
    sqlite3_stmt *stmt = db_execute_stmt_for(query, db);
    int chat_total = sqlite3_column_int64(stmt, 0);
    sqlite3_finalize(stmt);

    sqlite3_close(db);

    return chat_total; // Return the total number of chats
}
