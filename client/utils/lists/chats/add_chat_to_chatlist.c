#include "../../../inc/client.h"

// Function to add a chat to the chat list
t_response_code add_chat_to_chatlist(cJSON *json, t_chat **chat_list, bool is_search)
{
    // Extract chat information from the JSON object
    cJSON *chat_id = cJSON_GetObjectItem(json, "chat_id");
    cJSON *chat_name = cJSON_GetObjectItemCaseSensitive(json, "chat_name");
    cJSON *chat_color = cJSON_GetObjectItem(json, "chat_color");
    cJSON *chat_perms = cJSON_GetObjectItem(json, "chat_permissions");

    // Check if the required fields are present and have the correct types
    if (!cJSON_IsNumber(chat_id) || !cJSON_IsString(chat_name) ||
        !cJSON_IsNumber(chat_perms) || !cJSON_IsNumber(chat_color))
    {
        return R_JSON_FAILURE;
    }

    // Lock the mutex if it's not a search operation
    if (!is_search)
    {
        pthread_mutex_lock(&utils->lock);
    }

    // Add the chat to the chat list
    mx_chat_push_back(chat_list, chat_id->valueint, chat_name->valuestring,
                      chat_perms->valueint, chat_color->valueint);

    // Unlock the mutex if it's not a search operation
    if (!is_search)
    {
        pthread_mutex_unlock(&utils->lock);
    }

    // If it's not a search operation, request chat messages for the added chat
    if (!is_search)
    {
        handle_get_chat_msgs_request(chat_id->valueint);
    }

    return R_SUCCESS;
}
