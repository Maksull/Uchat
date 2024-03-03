#include "../inc/server.h"

// Function to retrieve username from database by user ID
char *db_get_username_by_id(int user_id)
{
    sqlite3 *db = open_database(); // Open database connection
    sqlite3_stmt *stmt; // SQLite prepared statement object
    sqlite3_prepare_v2(db, "SELECT `username` FROM `users` WHERE `id` = ?", -1, &stmt, NULL); // Prepare SQL statement
    sqlite3_bind_int64(stmt, 1, user_id); // Bind user_id parameter to SQL statement

    char *user_name = NULL; // Initialize variable to hold username
    if (sqlite3_step(stmt) == SQLITE_ROW) // Check if SQL query returned a row
    {
        user_name = mx_strdup((const char *)sqlite3_column_text(stmt, 0)); // Retrieve username from SQL result
    }
    sqlite3_finalize(stmt); // Finalize prepared statement
    sqlite3_close(db); // Close database connection

    return user_name; // Return retrieved username (or NULL if not found)
}
