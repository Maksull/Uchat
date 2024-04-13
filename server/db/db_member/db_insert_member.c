#include "../../inc/server.h"

// Function to retrieve the chat ID by name from the database
static int get_chat_id_by_name(const char *chat_name)
{
    // Create SQL query to retrieve the chat ID by name
    char query[QUERY_LEN];
    sprintf(query, "SELECT `id` FROM `chats` WHERE `name` = '%s'", chat_name);

    sqlite3 *db = open_db();

    // Execute the SQL query and retrieve the result
    sqlite3_stmt *sql_stmt = db_execute_sql_stmt(query, db); // Execute SQL query
    int chat_id = -1;                                        // Initialize chat ID with a default value

    // Check if the query returned a result
    if (sqlite3_step(sql_stmt) == SQLITE_ROW)
    {
        // Get the chat ID from the query result
        chat_id = sqlite3_column_int64(sql_stmt, 0);
    }

    sqlite3_finalize(sql_stmt); // Finalize the statement
    sqlite3_close(db);

    return chat_id; // Return the chat ID
}

// Function to insert a new member into a chat in the database
static t_response_code insert_member_into_chat(int user_id, int chat_id, t_member_type member_type)
{
    // Create SQL query to insert the new member into the chat
    char query[QUERY_LEN];
    snprintf(query, QUERY_LEN, "INSERT INTO `members` (`user_id`, `chat_id`, `permissions`) VALUES('%d', '%d', '%d')",
             user_id, chat_id, member_type);

    // Execute the SQL query
    if (db_execute_query(query) != 0)
    {
        return R_DB_FAILURE; // Return failure code if insertion fails
    }

    return R_SUCCESS; // Return success code if insertion is successful
}

// Insert a new member into a chat in the database
int db_insert_member(const char *chat_name, t_member_type member_type, t_server_utils *utils)
{
    int user_id = utils->user->user_id;           // Get the user ID
    int chat_id = get_chat_id_by_name(chat_name); // Retrieve the chat ID by name

    // Check if the chat ID is valid
    if (chat_id == -1)
    {
        return R_CHAT_NOENT; // Return chat does not exist code
    }

    // Insert the new member into the chat
    return insert_member_into_chat(user_id, chat_id, member_type);
}
