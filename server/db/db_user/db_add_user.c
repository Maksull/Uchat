#include "../../inc/server.h"

// Function to validate user information
static t_response_code validate_user_info(const cJSON *user_info)
{
    // Variables to hold user information
    const cJSON *user_name = cJSON_GetObjectItemCaseSensitive(user_info, "name");
    const cJSON *user_password = cJSON_GetObjectItemCaseSensitive(user_info, "password");
    const cJSON *avatar_color = cJSON_GetObjectItemCaseSensitive(user_info, "avatar_color");

    // Check if user information is valid
    if (!cJSON_IsString(user_name) || !cJSON_IsString(user_password) || !cJSON_IsNumber(avatar_color))
    {
        return R_JSON_FAILURE;
    }

    // Check if user already exists in the database
    if (db_user_exists(user_name->valuestring))
    {
        return R_USR_EXISTS;
    }

    // Validate user name length and format
    if (!is_strlen_valid(user_name->valuestring, MIN_NAME_INPUT_LEN, MAX_NAME_INPUT_LEN) ||
        !is_user_name_format_valid(user_name->valuestring))
    {
        return R_NAME_LEN_INVALID;
    }

    // Validate password length
    if (!is_strlen_valid(user_password->valuestring, MIN_PASS_INPUT_LEN, MAX_PASS_INPUT_LEN))
    {
        return R_PASS_LEN_INVALID;
    }

    return R_SUCCESS;
}

// Function to add a user to the database
t_response_code db_add_user(const cJSON *user_info)
{
    // Validate user information
    t_response_code validation_result = validate_user_info(user_info);
    if (validation_result != R_SUCCESS)
    {
        return validation_result;
    }

    // Extract user information
    const cJSON *user_name = cJSON_GetObjectItemCaseSensitive(user_info, "name");
    const cJSON *user_password = cJSON_GetObjectItemCaseSensitive(user_info, "password");
    const cJSON *avatar_color = cJSON_GetObjectItemCaseSensitive(user_info, "avatar_color");

    // Construct SQL query to insert user into database
    char query[QUERY_LEN];
    sprintf(query, "INSERT INTO `users` (`username`, `password`, `avatar_color`) VALUES('%s', '%s', '%d')",
            user_name->valuestring, user_password->valuestring, avatar_color->valueint);

    // Execute SQL query to insert user into database
    if (db_execute_query(query) != 0)
    {
        return R_DB_FAILURE;
    }

    return R_SUCCESS;
}
