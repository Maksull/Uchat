#include "../../inc/client.h"

// Handle response to get a message
t_msg *handle_get_msg_res()
{
    // Receive response from the server
    char *response_str = receive_from_server(utils->ssl);

    // Check if response is NULL
    if (response_str == NULL)
    {
        return NULL;
    }

    // Parse JSON response
    cJSON *json = cJSON_Parse(response_str);

    // Get error code from response
    int error_code = get_res_code(json);
    // Check if error code indicates success
    if (error_code != R_SUCCESS)
    {
        cJSON_Delete(json); // Delete JSON object to free memory
        logger(get_res_str(error_code), ERROR_LOG); // Log error message
        
        return NULL;
    }

    // Get message JSON object from response
    cJSON *msg_json = cJSON_GetObjectItem(json, "message");
    // Get message from JSON object
    t_msg *new_msg = get_msg_from_json(msg_json);

    cJSON_Delete(json); // Delete JSON object to free memory

    // Check if message is NULL or sender ID is the same as current user's ID
    if (new_msg == NULL || new_msg->sender_id == utils->current_user->user_id)
    {
        logger(get_res_str(R_JSON_FAILURE), ERROR_LOG); // Log error message

        return NULL;
    }

    free(response_str); // Free memory allocated for response string
    return new_msg; // Return the message
}
