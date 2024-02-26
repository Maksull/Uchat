#include "../inc/server.h"

// Delete a user by user ID
t_response_code db_delete_user(int user_id)
{
    // Check if the user exists
    if (!db_get_username_by_id(user_id))
    {
        return R_USR_NOENT; // User does not exist
    }

    // Construct the SQL query to delete the user
    char query[QUERY_LEN];
    sprintf(query, "DELETE FROM `users` WHERE `id` = '%d'", user_id);

    // Execute the SQL query and check for errors
    if (db_execute_query(query) != 0)
    {
        return R_DB_FAILURE; // Database operation failed
    }

    // Return success if the deletion was successful
    return R_SUCCESS;
}
