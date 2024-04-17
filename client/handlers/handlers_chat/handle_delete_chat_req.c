#include "../../inc/client.h"

// Function to create a JSON object for deleting a chat request
static cJSON *create_delete_chat_json(const char *chat_name)
{
    // Create JSON object for the request
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "name", chat_name);
    cJSON_AddNumberToObject(json, "type", REQ_DELETE_CHAT);

    return json;
}

// Function to handle deleting a chat request
int handle_delete_chat_req(const char *chat_name)
{
    // Set the client as suspended
    utils->is_suspended = true;

    // Create JSON object for the request
    cJSON *json = create_delete_chat_json(chat_name);
    char *json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    // Send request to server and receive response
    char *response = send_and_receive_from_server(utils->ssl, json_str);
    // Handle the server response
    int error_code = handle_server_res(response);
    // Log the response
    logger(get_res_str(error_code), error_code == R_SUCCESS ? INFO_LOG : ERROR_LOG);

    // If response is successful, handle getting chats request
    (error_code == R_SUCCESS) ? handle_get_chats_req() : (void)0;

    // Free memory
    free(json_str);
    free(response);

    // Set the client as not suspended
    utils->is_suspended = false;

    return error_code;
}
