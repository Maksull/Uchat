#include "../../inc/server.h"

// Insert a new chat into the database
t_response_code db_insert_chat(const char *chat_name, int date, int avatar_color)
{
    // Check if the chat already exists in the database
    int chat_id = db_get_chat_id_by_name(chat_name); // Get the chat ID by name
    if (chat_id != -1)
    {
        return R_CHAT_EXISTS; // Return chat exists error code if chat already exists
    }

    // Create SQL query to insert the new chat into the database
    char query[QUERY_LEN];
    sprintf(query, "INSERT INTO `chats` (`name`, `date`, `avatar_color`) VALUES('%s', '%d', '%d')",
            chat_name, date, avatar_color);

    // Execute the SQL query
    if (db_execute_query(query) != 0)
    {
        return R_DB_FAILURE; // Return database failure error code if insertion fails
    }

    return R_SUCCESS;
}
