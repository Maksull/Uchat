#include "../inc/server.h"

// Execute a single SQLite statement without finalizing it
sqlite3_stmt *db_execute_sql_stmt(const char *query, sqlite3 *db)
{
    sqlite3_stmt *sql_stmt; // SQLite statement pointer

    sqlite3_prepare_v2(db, query, -1, &sql_stmt, NULL); // Prepare the SQL statement

    sqlite3_step(sql_stmt); // Execute the prepared statement

    return sql_stmt; // Return the SQLite statement pointer
}
