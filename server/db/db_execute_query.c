#include "../inc/server.h"

// Function to execute a database query
int db_execute_query(const char *query)
{
    sqlite3 *db = open_db(); // Open the database connection

    char *error_message;

    // Execute the SQL query
    if (sqlite3_exec(db, query, NULL, NULL, &error_message))
    {
        logger(error_message, ERROR_LOG);
        return 1;
    }

    sqlite3_close(db);

    return 0;
}
