#include "../inc/server.h"

// Delete a member from all chats by user ID
t_response_code db_delete_member_by_user_id(int user_id)
{
    // Construct the SQL query to delete the member from all chats
    char query[QUERY_LEN];
    sprintf(query, "DELETE FROM `members` WHERE `user_id` = '%d'", user_id);

    // Execute the SQL query and check for errors
    if (db_execute_query(query) != 0)
    {
        return R_DB_FAILURE;
    }

    // Return success if the deletion was successful
    return R_SUCCESS;
}
