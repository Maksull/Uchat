#include "../inc/client.h"

// Function to handle send message response
t_response_code handle_send_msg_response(const char *response_str, t_msg *sent_msg)
{
    // Check for invalid input
    if (response_str == NULL)
    {
        return R_INVALID_INPUT;
    }

    // Parse the response JSON
    cJSON *json = cJSON_Parse(response_str);
    int error_code = get_response_code(json);

    // Handle response error code
    if (error_code != R_SUCCESS)
    {
        // Clear the sent message and delete the JSON object
        mx_clear_msg(&sent_msg);
        cJSON_Delete(json);
        return error_code;
    }

    // Get the message ID from the response
    cJSON *msg_id = cJSON_GetObjectItem(json, "message_id");
    sent_msg->message_id = msg_id->valueint;

    // Add the sent message to the global message list
    if ((error_code = add_to_global_msglist(sent_msg)) != R_SUCCESS)
    {
        return error_code;
    }

    // Delete the JSON object
    cJSON_Delete(json);

    return R_SUCCESS;
}
