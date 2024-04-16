#include "../../inc/client.h"

// Function to handle edit chat request
t_response_code handle_edit_chat_req(int chat_id, const char *new_name)
{
    // Set the client as suspended
    utils->is_suspended = true;

    // Create JSON object for the request
    cJSON *json = create_edit_chat_json(chat_id, new_name);
    char *json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    // Send request to server and receive response
    char *response = send_and_receive_from_server(utils->ssl, json_str);
    // Handle the server response
    t_response_code error_code = handle_server_res(response);
    // Log the response
    logger(get_res_str(error_code), error_code == R_SUCCESS ? INFO_LOG : ERROR_LOG);

    // If response is successful, handle get chats request
    (error_code == R_SUCCESS) ? handle_get_chats_req() : (void)0;

    // Free memory
    free(json_str);
    free(response);

    // Set the client as not suspended
    utils->is_suspended = false;

    return error_code;
}
