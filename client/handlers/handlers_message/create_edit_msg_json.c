#include "../../inc/client.h"

// Function to create a JSON object for editing a message request
cJSON *create_edit_msg_json(int message_id, const char *new_msg_text) {
    // Create JSON object for the request
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", REQ_EDIT_MESSAGE);
    cJSON_AddNumberToObject(json, "id", message_id);
    cJSON_AddStringToObject(json, "text", new_msg_text);
    cJSON_AddNumberToObject(json, "user_id", utils->current_user->user_id);
    cJSON_AddNumberToObject(json, "chat_id", utils->current_chat->id);

    return json;
}
