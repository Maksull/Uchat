#include "../../inc/server.h"

// Modify user name by user ID
t_response_code db_modify_user_name(int user_id, const char *new_name)
{
    // Construct the SQL query to update the username
    char query[QUERY_LEN];
    sprintf(query, "UPDATE `users` SET `username` = '%s' WHERE `id` = '%d'", new_name, user_id);

    // Execute the SQL query and check for errors
    if (db_execute_query(query) != 0)
    {
        return R_DB_FAILURE; // Database operation failed
    }

    // Return success if the modification was successful
    return R_SUCCESS;
}
