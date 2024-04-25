#include "../../inc/server.h"

// Function to construct the SQL query to update the username
static void construct_username_update_query(char *query, int user_id, const char *new_name)
{
    sprintf(query, "UPDATE `users` SET `username` = '%s' WHERE `id` = '%d'", new_name, user_id);
}

// Modify user name by user ID
t_response_code db_modify_user_name(int user_id, const char *new_name)
{
    // Construct the SQL query to update the username
    char query[QUERY_LEN];
    construct_username_update_query(query, user_id, new_name);

    // Execute the SQL query and check for errors
    if (db_execute_query(query) != 0)
    {
        return R_DB_FAILURE; // Database operation failed
    }

    // Return success if the modification was successful
    return R_SUCCESS;
}
