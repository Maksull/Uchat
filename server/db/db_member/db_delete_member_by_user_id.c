#include "../../inc/server.h"

// Function to construct the SQL query to delete a member from all chats by user ID
static void construct_delete_member_query(char *query, int user_id)
{
    // Construct the SQL query to delete the member from all chats
    snprintf(query, QUERY_LEN, "DELETE FROM `members` WHERE `user_id` = '%d'", user_id);
}

// Delete a member from all chats by user ID
t_response_code db_delete_member_by_user_id(int user_id)
{
    char query[QUERY_LEN];

    // Construct the SQL query to delete the member from all chats
    construct_delete_member_query(query, user_id);

    // Execute the SQL query and check for errors
    if (db_execute_query(query) != 0)
    {
        return R_DB_FAILURE;
    }

    // Return success if the deletion was successful
    return R_SUCCESS;
}
