#include "../../inc/server.h"

// Function to get the chat ID by its name from the database
static int get_chat_id_by_name_from_db(const char *chat_name, sqlite3 *db)
{
    // Declare a SQLite3 statement object.
    sqlite3_stmt *sql_stmt;
    // Prepare the SQL statement to select the ID of the chat with the specified name.
    sqlite3_prepare_v2(db, "SELECT `id` FROM `chats` WHERE `name` = ?", -1, &sql_stmt, NULL);
    // Bind the chat name parameter to the SQL statement.
    sqlite3_bind_text(sql_stmt, 1, chat_name, -1, NULL);

    // Initialize the chat ID to -1 (indicating not found).
    int chat_id = -1;

    // Execute the SQL statement and check if a row is returned.
    if (sqlite3_step(sql_stmt) == SQLITE_ROW)
    {
        // If a row is returned, extract the chat ID from the result.
        chat_id = sqlite3_column_int64(sql_stmt, 0);
    }

    // Finalize the SQL statement to release resources.
    sqlite3_finalize(sql_stmt);

    // Return the chat ID (found or -1 if not found).
    return chat_id;
}

// Original function refactored
int db_get_chat_id_by_name(const char *chat_name)
{
    // Open the database connection.
    sqlite3 *db = open_db();
    // Retrieve the chat ID from the database.
    int chat_id = get_chat_id_by_name_from_db(chat_name, db);
    // Close the database connection.
    sqlite3_close(db);

    // Return the chat ID.
    return chat_id;
}
