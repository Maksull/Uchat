#include "../../inc/server.h"

// Function to check if a chat exists in the database
static bool chat_exists_in_db(int chat_id, sqlite3 *db)
{
    // Define a buffer to hold the SQL query.
    char query[QUERY_LEN];
    // Construct the SQL query to check if the chat ID exists in the 'chats' table.
    sprintf(query, "SELECT EXISTS (SELECT `id` FROM `chats` WHERE `id` = '%d')", chat_id);

    // Execute the SQL query and retrieve the result.
    sqlite3_stmt *sql_stmt = db_execute_sql_stmt(query, db);
    // Extract the result of the query (0 or 1) indicating whether the chat exists.
    int chat_exists = sqlite3_column_int64(sql_stmt, 0);
    // Finalize the SQL statement to release resources.
    sqlite3_finalize(sql_stmt);

    // Return true if the chat exists in the database (chat_exists == 1), otherwise false.
    return chat_exists == 1;
}

// Original function refactored
bool db_chat_exists(int chat_id)
{
    // Open the database connection.
    sqlite3 *db = open_db();
    // Check if the chat exists in the database.
    bool exists = chat_exists_in_db(chat_id, db);
    // Close the database connection.
    sqlite3_close(db);

    // Return the result indicating whether the chat exists in the database.
    return exists;
}
