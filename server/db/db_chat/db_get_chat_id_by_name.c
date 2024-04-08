#include "../../inc/server.h"

// Get the chat ID by its name from the database
int db_get_chat_id_by_name(const char *chat_name)
{
    sqlite3 *db = open_db(); // Open the database connection

    // Prepare SQL statement to select the chat ID by name
    sqlite3_stmt *sql_stmt;
    sqlite3_prepare_v2(db, "SELECT `id` FROM `chats` WHERE `name` = ?", -1, &sql_stmt, NULL);
    sqlite3_bind_text(sql_stmt, 1, chat_name, -1, NULL);

    int chat_id = -1; // Initialize chat ID variable

    // Execute the SQL statement and retrieve the result
    if (sqlite3_step(sql_stmt) == SQLITE_ROW)
    {
        // If the query returns a row, extract the chat ID
        chat_id = sqlite3_column_int64(sql_stmt, 0); // Get the chat ID from the result set
    }

    sqlite3_finalize(sql_stmt);
    sqlite3_close(db);

    // Return the chat ID (or -1 if not found)
    return chat_id;
}
