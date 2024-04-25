#include "../../inc/server.h"

// Function to check if a user exists by user ID
static bool user_exists(int user_id)
{
    return db_get_username_by_id(user_id) != NULL;
}

// Function to delete a user from the database
static t_response_code delete_user_from_db(int user_id)
{
    // Construct the SQL query to delete the user
    char query[QUERY_LEN];
    sprintf(query, "DELETE FROM `users` WHERE `id` = '%d'", user_id);

    // Execute the SQL query and check for errors
    if (db_execute_query(query) != 0)
    {
        return R_DB_FAILURE; // Database operation failed
    }

    return R_SUCCESS;
}

// Function to delete a user by user ID
t_response_code db_delete_user(int user_id)
{
    // Check if the user exists
    if (!user_exists(user_id))
    {
        return R_USR_NOENT; // User does not exist
    }

    // Delete the user from the database
    return delete_user_from_db(user_id);
}
