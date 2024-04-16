#include "../../inc/client.h"

// Function to create a JSON object for searching chats request
cJSON *create_search_chats_json(const char *search_str) {
    // Create JSON object for the request
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "search_pattern", search_str);
    cJSON_AddNumberToObject(json, "type", REQ_SEARCH_CHATS);

    return json;
}
