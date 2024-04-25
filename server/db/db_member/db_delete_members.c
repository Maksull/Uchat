#include "../../inc/server.h"

// Function to construct the SQL query
static void construct_delete_members_query(char *query, int chat_id)
{
    // Construct the SQL query to delete members of the specified chat
    snprintf(query, QUERY_LEN, "DELETE FROM `members` WHERE `chat_id` = '%d'", chat_id);
}

// Delete members of a chat from the database
int db_delete_members(int chat_id)
{
    char query[QUERY_LEN];

    // Construct the SQL query to delete members of the specified chat
    construct_delete_members_query(query, chat_id);

    // Execute the SQL query and check for errors
    if (db_execute_query(query) != 0)
    {
        return R_DB_FAILURE; // Return database failure code
    }

    return R_SUCCESS; // Return success code
}
