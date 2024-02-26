#include "../inc/server.h"

// Delete members of a chat from the database
int db_delete_members(int chat_id)
{
    // Create SQL query to delete members of the specified chat
    char query[QUERY_LEN];
    sprintf(query, "DELETE FROM `members` WHERE `chat_id` = '%d'", chat_id);

    // Execute the SQL query
    if (db_execute_query(query) != 0)
    {
        return R_DB_FAILURE;
    }

    return R_SUCCESS;
}
