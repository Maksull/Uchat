#include "../../inc/client.h"

// Function to create a JSON object for editing a chat request
cJSON *create_edit_chat_json(int chat_id, const char *new_name) {
    // Create JSON object for the request
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "chat_id", chat_id);
    cJSON_AddStringToObject(json, "chat_name", new_name);
    cJSON_AddNumberToObject(json, "type", REQ_EDIT_CHAT);

    return json;
}
