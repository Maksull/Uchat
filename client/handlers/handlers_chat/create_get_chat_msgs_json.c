#include "../../inc/client.h"

// Function to create a JSON object for getting chat messages request
cJSON *create_get_chat_msgs_json(int chat_id) {
    // Create JSON object for the request
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "chat_id", chat_id);
    cJSON_AddNumberToObject(json, "type", REQ_GET_CHAT_MSGS);

    return json;
}
