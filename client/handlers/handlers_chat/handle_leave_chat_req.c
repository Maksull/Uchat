#include "../../inc/client.h"

// Function to create a JSON object for leaving a chat request
static cJSON *create_leave_chat_json(const char *chat_name)
{
    // Create JSON object for the request
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "name", chat_name);
    cJSON_AddNumberToObject(json, "type", REQ_LEAVE_CHAT);

    return json;
}

// Function to handle leave chat request
t_response_code handle_leave_chat_req(const char *chat_name)
{
    // Suspend operations
    utils->is_suspended = true;

    // Create JSON object for the request
    cJSON *json = create_leave_chat_json(chat_name);
    char *json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    // Send request to server and receive response
    char *response = send_and_receive_from_server(utils->ssl, json_str);

    // Handle server response
    int error_code = handle_server_res(response);
    // Log response
    logger(get_res_str(error_code), error_code == R_SUCCESS ? INFO_LOG : ERROR_LOG);

    // If leave chat request successful, update chat list
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
