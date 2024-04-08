#include "../../inc/server.h"

// Insert a new member into a chat in the database
int db_insert_member(const char *chat_name, t_member_type member_type, t_server_utils *utils)
{
    // Create SQL query to retrieve the chat ID by name
    char query[QUERY_LEN];
    sprintf(query, "SELECT `id` FROM `chats` WHERE `name` = '%s'", chat_name);

    sqlite3 *db = open_db();

    // Execute the SQL query and retrieve the result
    sqlite3_stmt *sql_stmt = db_execute_sql_stmt(query, db); // Execute SQL query
    int user_id = utils->user->user_id;                  // Get the user ID
    int chat_id = sqlite3_column_int64(sql_stmt, 0);         // Get the chat ID
    sqlite3_finalize(sql_stmt);                              // Finalize the statement

    sqlite3_close(db);

    bzero(query, QUERY_LEN); // Clear the query buffer

    // Create SQL query to insert the new member into the chat
    sprintf(query,
            "INSERT INTO `members` (`user_id`, `chat_id`, `permissions`) VALUES('%d', '%d', '%d')",
            user_id, chat_id, member_type);

    // Execute the SQL query
    if (db_execute_query(query) != 0)
    {
        return R_DB_FAILURE; // Return failure code if insertion fails
    }

    return R_SUCCESS; // Return success code if insertion is successful
}
