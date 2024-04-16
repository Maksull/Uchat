#include "../../inc/client.h"

// Function to create a JSON object for creating a chat request
cJSON *create_chat_json(const char *chat_name) {
    // Create JSON object for the request
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "name", chat_name);
    cJSON_AddNumberToObject(json, "date", get_current_time());
    cJSON_AddNumberToObject(json, "avatar_color", get_avatar_color());
    cJSON_AddNumberToObject(json, "type", REQ_CREATE_CHAT);

    return json;
}
