#include "../../inc/server.h"

// Check if a chat exists in the database
bool db_chat_exists(int chat_id)
{
    // Create SQL query to check if chat with given ID exists
    char query[QUERY_LEN]; // Buffer to hold SQL query
    sprintf(query, "SELECT EXISTS (SELECT `id` FROM `chats` WHERE `id` = '%d')", chat_id);

    sqlite3 *db = open_db(); // Open the database connection

    // Execute the SQL statement and get the result
    sqlite3_stmt *stmt = db_execute_stmt_for(query, db);
    int chat_exists = sqlite3_column_int64(stmt, 0);
    sqlite3_finalize(stmt);

    sqlite3_close(db);

    return chat_exists == 1; // Return true if chat exists, false otherwise
}
