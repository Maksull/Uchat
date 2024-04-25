#include "../inc/server.h"

// Function to execute a single SQLite statement without finalizing it
sqlite3_stmt *db_execute_sql_stmt(const char *query, sqlite3 *db)
{
    sqlite3_stmt *sql_stmt = NULL; // SQLite statement pointer

    // Prepare the SQL statement
    int prepare_result = sqlite3_prepare_v2(db, query, -1, &sql_stmt, NULL);
    if (prepare_result != SQLITE_OK)
    {
        // Log error message
        logger("Failed to prepare SQL statement", ERROR_LOG);
        return NULL; // Return NULL to indicate failure
    }

    // Execute the prepared statement
    int step_result = sqlite3_step(sql_stmt);
    if (step_result != SQLITE_DONE && step_result != SQLITE_ROW)
    {
        // Log error message
        logger("Failed to execute SQL statement", ERROR_LOG);
        // Finalize the prepared statement
        sqlite3_finalize(sql_stmt);
        return NULL; // Return NULL to indicate failure
    }

    return sql_stmt; // Return the SQLite statement pointer
}
