#include "../../inc/server.h"

// Function to handle username editing
void handle_edit_username(const cJSON *user_info, t_server_utils *utils)
{
    // Initialize the database
    if (init_db() != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_EDIT_USERNAME);
        return;
    }

    // Get the new username from the JSON object
    const cJSON *new_name = cJSON_GetObjectItemCaseSensitive(user_info, "name");

    // Check if the new username is a valid string
    if (!cJSON_IsString(new_name))
    {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_EDIT_USERNAME);
        return;
    }

    // Error code for handling errors
    int error_code = 0;

    // Check if the new username already exists
    if (db_user_exists(new_name->valuestring))
    {
        send_server_response(utils->ssl, R_USR_EXISTS, REQ_EDIT_USERNAME);
        return;
    }

    // Check if the new username meets length requirements
    if (!is_strlen_valid(new_name->valuestring, MIN_NAME_INPUT_LEN, MAX_NAME_INPUT_LEN))
    {
        send_server_response(utils->ssl, R_NAME_LEN_INVALID, REQ_EDIT_USERNAME);
        return;
    }

    // Check if the new username format is valid
    if (!is_user_name_format_valid(new_name->valuestring))
    {
        send_server_response(utils->ssl, R_NAME_FORMAT_INVALID, REQ_EDIT_USERNAME);
        return;
    }

    // Modify the user's username in the database
    if ((error_code = db_modify_user_name(utils->user->user_id, new_name->valuestring)) != R_SUCCESS)
    {
        send_server_response(utils->ssl, error_code, REQ_EDIT_USERNAME);
        return;
    }

    // Send success response
    send_server_response(utils->ssl, R_SUCCESS, REQ_EDIT_USERNAME);
}
