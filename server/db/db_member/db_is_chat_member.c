#include "../../inc/server.h"

// Function to prepare and execute the SQL query to check if a user is a member of a chat
static int execute_check_membership_query(int user_id, int chat_id)
{
    // Create SQL query to check if the user is a member of the chat
    char query[QUERY_LEN]; // Buffer to hold SQL query
    snprintf(query, QUERY_LEN,
             "SELECT EXISTS (SELECT `id` FROM `members` WHERE `user_id` = '%d' AND `chat_id` = '%d')",
             user_id, chat_id); // Format SQL query

    sqlite3 *db = open_db();

    // Execute the SQL query and retrieve the result
    sqlite3_stmt *sql_stmt = db_execute_sql_stmt(query, db);
    int is_chat_member = sqlite3_column_int64(sql_stmt, 0);
    sqlite3_finalize(sql_stmt);

    sqlite3_close(db);

    return is_chat_member; // Return the result
}

// Check if a user is a member of a chat
bool db_is_chat_member(int user_id, int chat_id)
{
    // Execute the SQL query to check if the user is a member of the chat
    int is_chat_member = execute_check_membership_query(user_id, chat_id);

    return is_chat_member == 1; // Return true if the user is a member, false otherwise
}
