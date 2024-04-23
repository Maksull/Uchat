#include "../../inc/client.h"

// Function to create a JSON object for getting chats request
static cJSON *create_get_chats_json()
{
    // Create JSON object for the request
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", REQ_GET_CHATS);

    return json;
}

// Function to handle request for getting chats
t_response_code handle_get_chats_req()
{
    // Create JSON object for the request
    cJSON *json = create_get_chats_json();
    char *json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    int error_code = 0;
    // Send request and receive response from the server
    char *response = send_and_receive_from_server(utils->ssl, json_str);
    free(json_str);

    int curr_chat_id = -1;
    // Get the ID of the current chat, if exists
    if (utils->current_chat)
    {
        curr_chat_id = utils->current_chat->id;
    }

    free(response);

    // Handle the response
    if ((error_code = handle_get_chats_res(&utils->chatlist, response, false)) != R_SUCCESS)
    {
        logger(get_res_str(error_code), ERROR_LOG);
        return error_code;
    }

    // Set the current chat back to what it was before, if it exists
    if (curr_chat_id >= 0)
    {
        utils->current_chat = mx_get_chat_by_id(utils->chatlist, curr_chat_id);
    }

    return R_SUCCESS;
}
