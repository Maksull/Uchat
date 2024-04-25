#include "../../inc/server.h"

// Function to check if a user has specific permissions for a chat in the database
static bool user_has_chat_perms_in_db(int user_id, int chat_id, t_member_type perms, sqlite3 *db)
{
    // Define a buffer to hold the SQL query.
    char query[QUERY_LEN];
    // Construct the SQL query to retrieve the permissions of the user for the chat.
    sprintf(query, "SELECT `permissions` FROM `members` WHERE `user_id` = '%d' AND `chat_id` = '%d'", user_id, chat_id);

    // Execute the SQL query to retrieve the permissions.
    sqlite3_stmt *sql_stmt = db_execute_sql_stmt(query, db);
    // Retrieve the permissions from the query result.
    int chat_perms = sqlite3_column_int64(sql_stmt, 0);
    // Finalize the SQL statement to release resources.
    sqlite3_finalize(sql_stmt);

    // Check if the user has the specified permissions for the chat.
    return (t_member_type)chat_perms == perms;
}

// Original function refactored
bool db_has_chat_perms(int user_id, int chat_id, t_member_type perms)
{
    // Open the database connection.
    sqlite3 *db = open_db();
    // Check if the user has the specified permissions for the chat.
    bool has_perms = user_has_chat_perms_in_db(user_id, chat_id, perms, db);
    // Close the database connection.
    sqlite3_close(db);

    // Return whether the user has the specified permissions for the chat.
    return has_perms;
}
