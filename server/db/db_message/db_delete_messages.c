#include "../../inc/server.h"

// Delete messages of a chat from the database
int db_delete_messages(int chat_id)
{
    // Create SQL query to delete messages of the specified chat
    char query[QUERY_LEN];
    sprintf(query, "DELETE FROM `messages` WHERE `chat_id` = '%d'", chat_id);

    // Execute the SQL query
    if (db_execute_query(query) != 0)
    {
        return R_DB_FAILURE;
    }

    return R_SUCCESS;
}
