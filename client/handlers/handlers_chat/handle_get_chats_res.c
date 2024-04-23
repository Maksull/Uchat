#include "../../inc/client.h"

// Function to handle response for getting chats
t_response_code handle_get_chats_res(t_chat **chat_list, const char *response_str, bool is_search)
{
    // Check if response string is valid
    if (response_str == NULL)
    {
        return R_INVALID_INPUT;
    }

    // Parse JSON response
    cJSON *json = cJSON_Parse(response_str);

    // Get error code from the response
    int error_code = get_res_code(json);
    if (error_code != R_SUCCESS)
    {
        cJSON_Delete(json);
        return error_code;
    }

    // Get the array of chats from the JSON response
    cJSON *chats_array = cJSON_GetObjectItemCaseSensitive(json, "chats");
    cJSON_Delete(json);
    if (!cJSON_IsArray(chats_array))
    {
        return R_JSON_FAILURE;
    }

    // Clear the chat list
    pthread_mutex_lock(&utils->lock);
    mx_clear_chat_list(chat_list);
    pthread_mutex_unlock(&utils->lock);

    cJSON *chat = NULL;
    // Iterate over each chat in the array
    for (int i = 0; i < cJSON_GetArraySize(chats_array); ++i)
    {
        chat = cJSON_GetArrayItem(chats_array, i);
        // Add the chat to the chat list
        if ((error_code = add_chat_to_chatlist(chat, chat_list, is_search)) != R_SUCCESS)
        {
            return error_code;
        }
    }

    return R_SUCCESS;
}
