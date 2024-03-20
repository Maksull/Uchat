#include "../inc/server.h"

// Execute a single SQLite statement without finalizing it
sqlite3_stmt *db_execute_stmt_for(const char *query, sqlite3 *db)
{
    sqlite3_stmt *stmt; // SQLite statement pointer

    sqlite3_prepare_v2(db, query, -1, &stmt, NULL); // Prepare the SQL statement

    sqlite3_step(stmt); // Execute the prepared statement

    return stmt; // Return the SQLite statement pointer
}
