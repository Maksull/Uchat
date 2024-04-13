#include "../../inc/server.h"

// Function to modify the name of a chat in the database
t_response_code modify_chat_name_in_db(int chat_id, const char *new_name, sqlite3 *db)
{
    // Check if a chat with the new name already exists
    int chat_id_for_check = db_get_chat_id_by_name(new_name);
    if (chat_id_for_check != -1)
    {
        return R_CHAT_EXISTS;
    }

    char query[QUERY_LEN];
    sprintf(query, "UPDATE `chats` SET `name` = '%s' WHERE `id` = '%d'", new_name, chat_id);

    // Execute the SQL query
    if (db_execute_query(query) != 0)
    {
        return R_DB_FAILURE;
    }

    return R_SUCCESS;
}

// Original function refactored
t_response_code db_modify_chat_name(int chat_id, const char *new_name)
{
    sqlite3 *db = open_db();
    t_response_code response = modify_chat_name_in_db(chat_id, new_name, db);
    sqlite3_close(db);

    return response;
}
