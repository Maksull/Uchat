#include "../../inc/client.h"

// Function to create a JSON object for searching chats request
static cJSON *create_search_chats_json(const char *search_str)
{
    // Create JSON object for the request
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "search_pattern", search_str);
    cJSON_AddNumberToObject(json, "type", REQ_SEARCH_CHATS);

    return json;
}

// Function to handle search chats request
t_chat *handle_search_chats_req(const char *search_str)
{
    // Suspend operations
    utils->is_suspended = true;

    // Create JSON object for search chats request
    cJSON *json = create_search_chats_json(search_str);
    char *json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    int error_code = 0;
    char *response = send_and_receive_from_server(utils->ssl, json_str);

    free(json_str);
    free(response);

    t_chat *chat_list = NULL;
    if ((error_code = handle_get_chats_res(&chat_list, response, true)) != R_SUCCESS)
    {
        // Log error and free memory
        logger(get_res_str(error_code), ERROR_LOG);
        utils->is_suspended = false;
        return NULL;
    }

    // Resume operations
    utils->is_suspended = false;

    return chat_list;
}
