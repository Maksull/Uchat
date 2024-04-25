#include "../../inc/server.h"

// Function to construct the SQL query to update the password
static void construct_password_update_query(char *query, int user_id, const char *password)
{
    sprintf(query, "UPDATE `users` SET `password` = '%s' WHERE `id` = '%d'", password, user_id);
}

// Function to execute the SQL query to update the password
static int execute_password_update_query(const char *query)
{
    return db_execute_query(query); // Execute the SQL query and return the result
}

// Modify the password of a user by user ID
t_response_code db_modify_password(int user_id, const char *password)
{
    // Construct the SQL query to update the password
    char query[QUERY_LEN];
    construct_password_update_query(query, user_id, password);

    // Execute the SQL query and check for errors
    if (execute_password_update_query(query) != 0)
    {
        return R_DB_FAILURE; // Database operation failed
    }

    // Return success if the modification was successful
    return R_SUCCESS;
}
