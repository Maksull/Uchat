#include "../../inc/client.h"

// Function to create a JSON object for getting a message request
cJSON *create_get_msg_json(int chat_id, int message_id) {
    // Create JSON object for the request
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", REQ_GET_MSG);
    cJSON_AddNumberToObject(json, "message_id", message_id);
    cJSON_AddNumberToObject(json, "chat_id", chat_id);

    return json;
}
