#include "../../inc/client.h"

// Function to handle join chat request
t_response_code handle_join_chat_req(const char *chat_name)
{
    // Suspend operations
    utils->is_suspended = true;

    // Create JSON object for the request
    cJSON *json = create_join_chat_json(chat_name);
    char *json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    // Send request to server and receive response
    char *response = send_and_receive_from_server(utils->ssl, json_str);

    // Handle server response
    t_response_code error_code = handle_server_res(response);
    // Log response
    logger(get_res_str(error_code), error_code == R_SUCCESS ? INFO_LOG : ERROR_LOG);

    // If join chat request successful, update chat list
    (error_code == R_SUCCESS) ? handle_get_chats_req() : (void)0;

    // Free memory and resume operations
    free(json_str);
    free(response);
    utils->is_suspended = false;

    return error_code;
}
