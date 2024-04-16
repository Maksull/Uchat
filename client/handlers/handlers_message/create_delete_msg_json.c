#include "../../inc/client.h"

// Function to create a JSON object for deleting a message request
cJSON *create_delete_msg_json(int message_id) {
    // Create JSON object for the request
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", REQ_DELETE_MESSAGE);
    cJSON_AddNumberToObject(json, "id", message_id);
    cJSON_AddNumberToObject(json, "user_id", utils->current_user->user_id);
    cJSON_AddNumberToObject(json, "chat_id", utils->current_chat->id);

    return json;
}
