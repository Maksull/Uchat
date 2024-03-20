#include "../inc/server.h"

// Modify the password of a user by user ID
t_response_code db_modify_password(int user_id, const char *password)
{
    // Construct the SQL query to update the password
    char query[QUERY_LEN];
    sprintf(query, "UPDATE `users` SET `password` = '%s' WHERE `id` = '%d'", password, user_id);

    // Execute the SQL query and check for errors
    if (db_execute_query(query) != 0)
    {
        return R_DB_FAILURE; // Database operation failed
    }

    // Return success if the modification was successful
    return R_SUCCESS;
}
