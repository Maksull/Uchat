#include "../../inc/server.h"

// Function to get the total number of chats associated with a user ID from the database
static int get_chats_total_from_db(int user_id, sqlite3 *db)
{
    // Define a buffer to hold the SQL query.
    char query[QUERY_LEN];
    // Construct the SQL query to count the total number of chats associated with the user ID.
    sprintf(query, "SELECT COUNT(*) FROM chats "
                   "INNER JOIN members ON members.chat_id = chats.id "
                   "WHERE members.user_id = %d",
            user_id);

    // Execute the SQL query to count the total number of chats.
    sqlite3_stmt *sql_stmt = db_execute_sql_stmt(query, db);
    // Retrieve the total number of chats from the query result.
    int chat_total = sqlite3_column_int64(sql_stmt, 0);
    // Finalize the SQL statement to release resources.
    sqlite3_finalize(sql_stmt);

    // Return the total number of chats associated with the user ID.
    return chat_total;
}

// Original function refactored
int db_get_chats_total(int user_id)
{
    // Open the database connection.
    sqlite3 *db = open_db();
    // Retrieve the total number of chats associated with the user ID.
    int chat_total = get_chats_total_from_db(user_id, db);
    // Close the database connection.
    sqlite3_close(db);

    // Return the total number of chats.
    return chat_total;
}
