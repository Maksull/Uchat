// Function to create a JSON object for sending a message request
cJSON *create_send_msg_req_json(const char *message_str, unsigned long curr_time) {
    // Create JSON object for the request
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", REQ_SEND_MESSAGE);
    cJSON_AddStringToObject(json, "text", message_str);
    cJSON_AddNumberToObject(json, "user_id", utils->current_user->user_id);
    cJSON_AddStringToObject(json, "user_name", utils->current_user->name);
    cJSON_AddNumberToObject(json, "chat_id", utils->current_chat->id);
    cJSON_AddNumberToObject(json, "date", curr_time);

    return json;
}
