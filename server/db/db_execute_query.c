#include "../inc/server.h"

// Function to execute a database query
int db_execute_query(const char *query)
{
    // Open the database connection
    sqlite3 *db = open_db();

    char *error_message = NULL;

    // Execute the SQL query
    int result = sqlite3_exec(db, query, NULL, NULL, &error_message);

    // Check for errors
    if (result != SQLITE_OK)
    {
        // Log error message
        logger(error_message, ERROR_LOG);
        // Free error message memory
        sqlite3_free(error_message);
        // Close the database connection
        sqlite3_close(db);
        return 1; // Error
    }

    // Close the database connection
    sqlite3_close(db);

    return 0; // Success
}
