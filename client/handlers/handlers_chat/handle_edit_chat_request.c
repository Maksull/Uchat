#include "../../inc/client.h"

// Function to handle edit chat request
t_response_code handle_edit_chat_request(int chat_id, const char *new_name)
{
    // Set the client as suspended
    utils->is_suspended = true;

    // Create JSON object for the request
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "chat_id", chat_id);
    cJSON_AddStringToObject(json, "chat_name", new_name);
    cJSON_AddNumberToObject(json, "type", REQ_EDIT_CHAT);
    char *json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    // Send request to server and receive response
    char *response = send_and_recv_from_server(utils->ssl, json_str);
    // Handle the server response
    t_response_code error_code = handle_server_response(response);
    // Log the response
    logger(get_response_str(error_code), error_code == R_SUCCESS ? INFO_LOG : ERROR_LOG);

    // If response is successful, handle get chats request
    if (error_code == R_SUCCESS)
    {
        handle_get_chats_request();
    }

    // Free memory
    free(json_str);
    free(response);

    // Set the client as not suspended
    utils->is_suspended = false;

    return error_code;
}
