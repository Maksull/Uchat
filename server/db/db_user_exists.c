#include "../inc/server.h"

// Check if a user exists in the database
bool db_user_exists(const char *username)
{
    char query[QUERY_LEN]; // Query string to check if user exists
    // Construct SQL query to check if user exists
    sprintf(query, "SELECT EXISTS (SELECT `id` FROM `users` WHERE `username` = '%s')", username);

    sqlite3 *db = open_database();                       // SQLite database connection
    sqlite3_stmt *stmt = db_execute_stmt_for(query, db); // SQLite statement

    int user_exists = sqlite3_column_int64(stmt, 0); // Get the result of the query (0 or 1)

    // Finalize the prepared statement and close the database connection
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return user_exists == 1; // Return true if user exists, otherwise false
}
