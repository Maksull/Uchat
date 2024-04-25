#include "../../inc/server.h"

// Function to construct the SQL query to check if a user exists
static void construct_user_existence_query(char *query, const char *username)
{
    sprintf(query, "SELECT EXISTS (SELECT `id` FROM `users` WHERE `username` = '%s')", username);
}

// Function to execute the SQL query to check if a user exists
static int execute_user_existence_query(const char *query)
{
    sqlite3 *db = open_db();                             // Open database connection
    sqlite3_stmt *stmt = db_execute_sql_stmt(query, db); // Execute SQL statement
    int user_exists = sqlite3_column_int64(stmt, 0);     // Get the result of the query (0 or 1)
    sqlite3_finalize(stmt);                              // Finalize the prepared statement
    sqlite3_close(db);                                   // Close database connection
    return user_exists;                                  // Return true if user exists, otherwise false
}

// Check if a user exists in the database
bool db_user_exists(const char *username)
{
    char query[QUERY_LEN];                                 // Query string to check if user exists
    construct_user_existence_query(query, username);       // Construct SQL query
    int user_exists = execute_user_existence_query(query); // Execute SQL query
    return user_exists == 1;                               // Return true if user exists, otherwise false
}
