#include "../../inc/client.h"

// Function to handle get chat messages request
t_response_code handle_get_chat_msgs_req(int chat_id)
{
    // Create JSON object for the request
    cJSON *json = create_get_chat_msgs_json(chat_id);
    char *json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    int error_code = 0;
    // Send request to server and receive response
    char *response = send_and_receive_from_server(utils->ssl, json_str);

    free(json_str);
    free(response);

    // Handle the response
    if ((error_code = handle_get_chat_msgs_res(response)) != R_SUCCESS)
    {
        logger(get_res_str(error_code), ERROR_LOG);
        return error_code;
    }

    return R_SUCCESS;
}
