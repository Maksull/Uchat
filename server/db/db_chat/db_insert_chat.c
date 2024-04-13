#include "../../inc/server.h"

// Function to insert a new chat into the database
t_response_code insert_chat_into_db(const char *chat_name, int date, int avatar_color, sqlite3 *db)
{
    // Check if the chat already exists in the database
    int chat_id = db_get_chat_id_by_name(chat_name);
    if (chat_id != -1)
    {
        return R_CHAT_EXISTS;
    }

    // Create SQL query to insert the new chat into the database
    char query[QUERY_LEN];
    sprintf(query, "INSERT INTO `chats` (`name`, `date`, `avatar_color`) VALUES('%s', '%d', '%d')",
            chat_name, date, avatar_color);

    // Execute the SQL query
    if (db_execute_query(query) != 0)
    {
        return R_DB_FAILURE;
    }

    return R_SUCCESS;
}

// Original function refactored
t_response_code db_insert_chat(const char *chat_name, int date, int avatar_color)
{
    sqlite3 *db = open_db();
    t_response_code response = insert_chat_into_db(chat_name, date, avatar_color, db);
    sqlite3_close(db);

    return response;
}
