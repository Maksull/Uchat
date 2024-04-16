#include "../../inc/client.h"

// Parse last message ID response
static t_response_code last_msg_id_res(const char *response_str, int *i_last_msg_id)
{
    // Check if response string is NULL
    if (response_str == NULL)
    {
        return R_INVALID_INPUT;
    }

    // Parse JSON response
    cJSON *json = cJSON_Parse(response_str);

    // Get error code from response
    int error_code = get_res_code(json);
    // Check if error code indicates success
    if (error_code != R_SUCCESS)
    {
        cJSON_Delete(json); // Delete JSON object to free memory
        return error_code; // Return error code
    }

    // Get last message ID from JSON response
    cJSON *last_msg_id = cJSON_GetObjectItem(json, "last_msg_id");
    cJSON_Delete(json); // Delete JSON object to free memory

    // Check if last_msg_id is a number
    if (!cJSON_IsNumber(last_msg_id))
    {
        return R_JSON_FAILURE;
    }

    // Store last message ID
    *i_last_msg_id = last_msg_id->valueint;

    return R_SUCCESS; // Return success
}

// Handle request for last message ID
int handle_last_msg_id_req(int chat_id)
{
    // Create JSON request object
    cJSON *json = create_last_msg_id_req_json(chat_id);
    char *json_str = cJSON_PrintUnformatted(json); // Convert JSON object to string
    cJSON_Delete(json); // Delete JSON object to free memory

    int error_code = 0;
    // Send JSON request and receive response from the server
    char *response = send_and_receive_from_server(utils->ssl, json_str);
    free(json_str); // Free memory allocated for JSON string

    int last_msg_id = 0;
    // Parse last message ID response
    if ((error_code = last_msg_id_res(response, &last_msg_id)) != R_SUCCESS)
    {
        logger(get_res_str(error_code), ERROR_LOG); // Log error message
        free(response); // Free memory allocated for response string
        return -1; // Return -1 indicating failure
    }

    free(response); // Free memory allocated for response string

    return last_msg_id; // Return last message ID
}
