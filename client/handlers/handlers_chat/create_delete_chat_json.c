#include "../../inc/client.h"

// Function to create a JSON object for deleting a chat request
cJSON *create_delete_chat_json(const char *chat_name) {
    // Create JSON object for the request
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "name", chat_name);
    cJSON_AddNumberToObject(json, "type", REQ_DELETE_CHAT);

    return json;
}
