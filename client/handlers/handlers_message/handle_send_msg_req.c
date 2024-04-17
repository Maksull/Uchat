#include "../../inc/client.h"

// Function to create a JSON object for sending a message request
static cJSON *create_send_msg_req_json(const char *message_str, unsigned long curr_time)
{
    // Create JSON object for the request
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", REQ_SEND_MESSAGE);
    cJSON_AddStringToObject(json, "text", message_str);
    cJSON_AddNumberToObject(json, "user_id", utils->current_user->user_id);
    cJSON_AddStringToObject(json, "user_name", utils->current_user->name);
    cJSON_AddNumberToObject(json, "chat_id", utils->current_chat->id);
    cJSON_AddNumberToObject(json, "date", curr_time);

    return json;
}

// Function to handle send messages request
t_response_code handle_send_msg_req(const char *message_str)
{
    utils->is_suspended = true; // Suspend the current operation

    unsigned long curr_time = get_current_time(); // Get the current time
    // Create a message object
    t_msg *sent_msg = mx_create_msg(-1, utils->current_user->user_id, utils->current_user->name, utils->current_chat->id,
                                    message_str, get_string_time(curr_time), utils->current_user->avatar_color);

    // Create JSON object representing the message
    cJSON *json = create_send_msg_req_json(message_str, curr_time);
    char *json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    char *response = send_and_receive_from_server(utils->ssl, json_str);             // Send JSON request to the server and receive response
    int error_code = handle_send_msg_res(response, sent_msg);                        // Handle the response and get the error code
    logger(get_res_str(error_code), error_code == R_SUCCESS ? INFO_LOG : ERROR_LOG); // Log the result of the request

    free(response);              // Free memory
    utils->is_suspended = false; // Resume the operation

    return error_code; // Return the response code
}
