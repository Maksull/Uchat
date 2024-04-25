#include "../../inc/server.h"

// Function to create SQL query for deleting messages of a chat
static void create_delete_messages_query(int chat_id, char *query)
{
    sprintf(query, "DELETE FROM `messages` WHERE `chat_id` = '%d'", chat_id);
}

// Function to delete messages of a chat from the database
int db_delete_messages(int chat_id)
{
    char query[QUERY_LEN];
    create_delete_messages_query(chat_id, query);

    if (db_execute_query(query) != 0)
    {
        return R_DB_FAILURE; // Database operation failed
    }

    return R_SUCCESS; // Messages deletion successful
}
