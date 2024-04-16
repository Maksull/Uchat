#include "../../inc/client.h"

// Function to create a JSON object for getting chats request
cJSON *create_get_chats_json() {
    // Create JSON object for the request
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", REQ_GET_CHATS);

    return json;
}
