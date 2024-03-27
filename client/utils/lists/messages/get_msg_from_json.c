#include "../../../inc/client.h"

// Function to create a message from JSON data
t_msg *get_msg_from_json(cJSON *json)
{
    // Extract message attributes from JSON object
    cJSON *msg_id = cJSON_GetObjectItem(json, "msg_id");
    cJSON *sender_id = cJSON_GetObjectItem(json, "sender_id");
    cJSON *sender_name = cJSON_GetObjectItemCaseSensitive(json, "sender_name");
    cJSON *sender_color = cJSON_GetObjectItem(json, "sender_color");
    cJSON *text = cJSON_GetObjectItemCaseSensitive(json, "text");
    cJSON *chat_id = cJSON_GetObjectItem(json, "chat_id");
    cJSON *date = cJSON_GetObjectItemCaseSensitive(json, "date");

    // Check if all required attributes are present and of the correct type
    if (!cJSON_IsNumber(msg_id) || !cJSON_IsNumber(sender_id) || !cJSON_IsNumber(chat_id) ||
        !cJSON_IsString(sender_name) || !cJSON_IsString(text) || !cJSON_IsNumber(date) || !cJSON_IsNumber(sender_color))
    {
        return NULL;
    }

    // Create and return the message object
    return mx_create_msg(msg_id->valueint, sender_id->valueint, sender_name->valuestring, chat_id->valueint,
                         text->valuestring, get_string_time(date->valueint), sender_color->valueint);
}
