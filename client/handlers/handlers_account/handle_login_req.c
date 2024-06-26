#include "../../inc/client.h"

// Function to create a JSON object for login request
static cJSON *create_login_json(const char *user_name, const char *user_password)
{
    // Create JSON object for the request
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "name", user_name);
    cJSON_AddStringToObject(json, "password", user_password);
    cJSON_AddNumberToObject(json, "type", REQ_USR_LOGIN);

    return json;
}

// Function to handle login request
t_response_code handle_login_req(const char *user_name, const char *user_password)
{
    // Suspend operations
    utils->is_suspended = true;

    // Create JSON object for the request
    cJSON *json = create_login_json(user_name, user_password);
    char *json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    // Send request to server and receive response
    char *response = send_and_receive_from_server(utils->ssl, json_str);

    // Handle login response
    t_response_code error_code = handle_login_res(response);

    // Log response
    logger(get_res_str(error_code), error_code == R_SUCCESS ? INFO_LOG : ERROR_LOG);

    // If login successful, get chat list
    if (error_code == R_SUCCESS)
    {
        handle_get_chats_req();
    }

    // Free memory and resume operations
    free(json_str);
    free(response);
    utils->is_suspended = false;

    return error_code;
}
