#include "../../inc/client.h"

// Function to create a JSON object for requesting the last message ID
cJSON *create_last_msg_id_req_json(int chat_id) {
    // Create JSON object for the request
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "chat_id", chat_id);
    cJSON_AddNumberToObject(json, "type", REQ_LAST_MSG_ID);

    return json;
}
