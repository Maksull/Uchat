#include "../../inc/server.h"

// Function to check the validity of the new username
static int check_username_validity(const cJSON *user_info, t_server_utils *utils)
{
    // Get the new username from the JSON object
    const cJSON *new_name = cJSON_GetObjectItemCaseSensitive(user_info, "name");

    // Check if the new username is a valid string
    if (!cJSON_IsString(new_name))
    {
        return R_JSON_FAILURE;
    }

    // Check if the new username already exists
    if (db_user_exists(new_name->valuestring))
    {
        return R_USR_EXISTS;
    }

    // Check if the new username meets length requirements
    if (!is_strlen_valid(new_name->valuestring, MIN_NAME_INPUT_LEN, MAX_NAME_INPUT_LEN))
    {
        return R_NAME_LEN_INVALID;
    }

    // Check if the new username format is valid
    if (!is_user_name_format_valid(new_name->valuestring))
    {
        return R_NAME_FORMAT_INVALID;
    }

    return R_SUCCESS;
}

// Function to modify the user's username in the database
static int modify_username(const cJSON *user_info, t_server_utils *utils)
{
    // Get the new username from the JSON object
    const cJSON *new_name = cJSON_GetObjectItemCaseSensitive(user_info, "name");

    // Modify the user's username in the database
    return db_modify_user_name(utils->user->user_id, new_name->valuestring);
}

// Function to handle username editing
void handle_edit_username(const cJSON *user_info, t_server_utils *utils)
{
    // Initialize the database
    if (init_db() != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_EDIT_USERNAME);
        return;
    }

    // Check username validity
    int validity_check_result = check_username_validity(user_info, utils);
    if (validity_check_result != R_SUCCESS)
    {
        send_server_response(utils->ssl, validity_check_result, REQ_EDIT_USERNAME);
        return;
    }

    // Modify the username
    if (modify_username(user_info, utils) != R_SUCCESS)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_EDIT_USERNAME);
        return;
    }

    // Send success response
    send_server_response(utils->ssl, R_SUCCESS, REQ_EDIT_USERNAME);
}
