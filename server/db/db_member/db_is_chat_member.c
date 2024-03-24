#include "../../inc/server.h"

// Check if a user is a member of a chat
bool db_is_chat_member(int user_id, int chat_id)
{
    // Create SQL query to check if the user is a member of the chat
    char query[QUERY_LEN]; // Buffer to hold SQL query
    sprintf(query,
            "SELECT EXISTS (SELECT `id` FROM `members` WHERE `user_id` = '%d' AND `chat_id` = '%d')",
            user_id, chat_id); // Format SQL query

    sqlite3 *db = open_database();

    // Execute the SQL query and retrieve the result
    sqlite3_stmt *stmt = db_execute_stmt_for(query, db);
    int is_chat_member = sqlite3_column_int64(stmt, 0);
    sqlite3_finalize(stmt);

    sqlite3_close(db);

    return is_chat_member == 1; // Return true if the user is a member, false otherwise
}
