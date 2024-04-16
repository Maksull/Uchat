#include "../../inc/client.h"

// Function to create a JSON object for joining a chat request
cJSON *create_join_chat_json(const char *chat_name) {
    // Create JSON object for the request
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "chat_name", chat_name);
    cJSON_AddNumberToObject(json, "type", REQ_JOIN_CHAT);

    return json;
}
