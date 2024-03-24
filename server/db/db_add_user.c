#include "../inc/server.h"

// Function to add a user to the database
t_response_code db_add_user(const cJSON *user_info)
{
    // Variables to hold user information
    const cJSON *user_name = cJSON_GetObjectItemCaseSensitive(user_info, "name");            // Get user name
    const cJSON *user_password = cJSON_GetObjectItemCaseSensitive(user_info, "password");    // Get user password
    const cJSON *avatar_color = cJSON_GetObjectItemCaseSensitive(user_info, "avatar_color"); // Get avatar color

    // Check if user information is valid
    if (!cJSON_IsString(user_name) || !cJSON_IsString(user_password) || !cJSON_IsNumber(avatar_color))
    {
        // If user information is not valid, return JSON failure response code
        return R_JSON_FAILURE;
    }

    // Check if user already exists in the database
    if (db_user_exists(user_name->valuestring))
    {
        // If user already exists, return user exists response code
        return R_USR_EXISTS;
    }

    // Validate user name length
    if (!is_strlen_valid(user_name->valuestring, MIN_NAME_INPUT_LEN, MAX_NAME_INPUT_LEN))
    {
        // If user name length is invalid, return invalid name length response code
        return R_NAME_LEN_INVALID;
    }
    // Validate user name format
    if (!is_user_name_format_valid(user_name->valuestring))
    {
        // If user name format is invalid, return invalid name format response code
        return R_NAME_FORMAT_INVALID;
    }

    // Validate password length
    if (!is_strlen_valid(user_password->valuestring, MIN_PASS_INPUT_LEN, MAX_PASS_INPUT_LEN))
    {
        // If password length is invalid, return invalid password length response code
        return R_PASS_LEN_INVALID;
    }

    // Construct SQL query to insert user into database
    char query[QUERY_LEN]; // Declare array to hold SQL query
    sprintf(query, "INSERT INTO `users` (`username`, `password`, `avatar_color`) VALUES('%s', '%s', '%d')",
            user_name->valuestring, user_password->valuestring, avatar_color->valueint); // Format SQL query string

    // Execute SQL query to insert user into database
    if (db_execute_query(query) != 0)
    {
        // If database query execution fails, return database failure response code
        return R_DB_FAILURE;
    }

    // Return success response code
    return R_SUCCESS;
}
