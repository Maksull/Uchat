#include "../../inc/server.h"

// Check if a user has specific permissions for a chat
bool db_has_chat_perms(int user_id, int chat_id, t_member_type perms)
{
    // Create SQL query to retrieve permissions for a user in a chat
    char query[QUERY_LEN];                                                                                               // Buffer to hold SQL query
    sprintf(query, "SELECT `permissions` FROM `members` WHERE `user_id` = '%d' AND `chat_id` = '%d'", user_id, chat_id); // Format SQL query

    sqlite3 *db = open_db();

    // Execute the SQL query and retrieve the result
    sqlite3_stmt *stmt = db_execute_stmt_for(query, db);
    int chat_perms = sqlite3_column_int64(stmt, 0); // Get the permissions for the user in the chat
    sqlite3_finalize(stmt);

    sqlite3_close(db);

    return (t_member_type)chat_perms == perms; // Return true if user has the specified permissions, false otherwise
}
