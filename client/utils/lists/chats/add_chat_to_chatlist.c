#include "../../../inc/client.h"

// Function to extract chat information from JSON object
static void extract_chat_info(cJSON *json, cJSON **chat_id, cJSON **chat_name, cJSON **chat_color, cJSON **chat_perms)
{
    // Extract chat information from the JSON object
    *chat_id = cJSON_GetObjectItem(json, "chat_id");
    *chat_name = cJSON_GetObjectItemCaseSensitive(json, "chat_name");
    *chat_color = cJSON_GetObjectItem(json, "chat_color");
    *chat_perms = cJSON_GetObjectItem(json, "chat_permissions");
}

// Function to check if the required fields in the chat JSON are valid
static bool are_chat_fields_valid(const cJSON *chat_id, const cJSON *chat_name, const cJSON *chat_perms, const cJSON *chat_color)
{
    return cJSON_IsNumber(chat_id) && cJSON_IsString(chat_name) &&
           cJSON_IsNumber(chat_perms) && cJSON_IsNumber(chat_color);
}

// Function to add a chat to the chat list
t_response_code add_chat_to_chatlist(cJSON *json, t_chat **chat_list, bool is_search)
{
    if (!json)
    {
        return R_JSON_FAILURE;
    }

    cJSON *chat_id, *chat_name, *chat_color, *chat_perms;
    // Extract chat information from the JSON object
    extract_chat_info(json, &chat_id, &chat_name, &chat_color, &chat_perms);

    // Check if the required fields are present and have the correct types
    if (!are_chat_fields_valid(chat_id, chat_name, chat_perms, chat_color))
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
        handle_get_chat_msgs_req(chat_id->valueint);
    }

    return R_SUCCESS;
}
