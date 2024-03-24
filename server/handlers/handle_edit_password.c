#include "../inc/server.h"

// Function to handle password editing
void handle_edit_password(const cJSON *pass_info, t_server_utils *utils)
{
    // Initialize the database
    if (init_database() != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_EDIT_PASSWORD);
        return;
    }

    // Error code for handling errors
    int error_code = 0;

    // Get the new and old passwords from the JSON object
    const cJSON *new_pass = cJSON_GetObjectItemCaseSensitive(pass_info, "new_password");
    const cJSON *old_pass = cJSON_GetObjectItemCaseSensitive(pass_info, "old_password");

    // Check if the passwords are valid strings
    if (!cJSON_IsString(new_pass) || !cJSON_IsString(old_pass))
    {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_EDIT_PASSWORD);
        return;
    }

    // Check if the old password matches the user's current password
    if (strcmp(utils->user->password, old_pass->valuestring) != 0)
    {
        send_server_response(utils->ssl, R_INVALID_PASS, REQ_EDIT_PASSWORD);
        return;
    }

    // Check if the new password meets the length requirements
    if (!is_strlen_valid(new_pass->valuestring, MIN_PASS_INPUT_LEN, MAX_PASS_INPUT_LEN))
    {
        send_server_response(utils->ssl, R_PASS_LEN_INVALID, REQ_EDIT_PASSWORD);
        return;
    }

    // Modify the user's password in the database
    if ((error_code = db_modify_password(utils->user->user_id, new_pass->valuestring)) != R_SUCCESS)
    {
        send_server_response(utils->ssl, error_code, REQ_EDIT_PASSWORD);
        return;
    }

    // Send success response
    send_server_response(utils->ssl, R_SUCCESS, REQ_EDIT_PASSWORD);
}
