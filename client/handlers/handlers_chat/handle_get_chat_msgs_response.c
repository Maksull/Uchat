#include "../../inc/client.h"

// Function to handle response for getting chat messages
t_response_code handle_get_chat_msgs_response(const char *response_str)
{
    // Check if response string is valid
    if (response_str == NULL)
    {
        return R_INVALID_INPUT;
    }

    // Parse JSON response
    cJSON *json = cJSON_Parse(response_str);

    // Get response code
    int error_code = get_response_code(json);
    if (error_code != R_SUCCESS)
    {
        cJSON_Delete(json);
        return error_code;
    }

    // Get the messages array from JSON
    cJSON *msg_array = cJSON_GetObjectItemCaseSensitive(json, "messages");
    // Check if it's an array
    if (!cJSON_IsArray(msg_array))
    {
        cJSON_Delete(json);
        return R_JSON_FAILURE;
    }

    cJSON *chat = NULL;
    // Iterate through the messages array
    for (int i = 0; i < cJSON_GetArraySize(msg_array); ++i)
    {
        chat = cJSON_GetArrayItem(msg_array, i);
        // Add message to message list
        if ((error_code = add_msg_to_msglist(chat)) != R_SUCCESS)
        {
            cJSON_Delete(json);
            return error_code;
        }
    }

    cJSON_Delete(json);
    return R_SUCCESS;
}
