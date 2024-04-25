#include "../../../inc/client.h"

// Function definition to extract message attributes from JSON object
static void extract_message_attributes(cJSON *json, cJSON **msg_id, cJSON **sender_id, cJSON **sender_name,
                                cJSON **sender_color, cJSON **text, cJSON **chat_id, cJSON **date)
{
    *msg_id = cJSON_GetObjectItem(json, "msg_id");
    *sender_id = cJSON_GetObjectItem(json, "sender_id");
    *sender_name = cJSON_GetObjectItemCaseSensitive(json, "sender_name");
    *sender_color = cJSON_GetObjectItem(json, "sender_color");
    *text = cJSON_GetObjectItemCaseSensitive(json, "text");
    *chat_id = cJSON_GetObjectItem(json, "chat_id");
    *date = cJSON_GetObjectItemCaseSensitive(json, "date");
}

// Function to check if the required attributes in the message JSON are valid
static bool are_message_attributes_valid(const cJSON *msg_id, const cJSON *sender_id, const cJSON *chat_id,
                                  const cJSON *sender_name, const cJSON *text, const cJSON *date,
                                  const cJSON *sender_color)
{
    return cJSON_IsNumber(msg_id) && cJSON_IsNumber(sender_id) && cJSON_IsNumber(chat_id) &&
           cJSON_IsString(sender_name) && cJSON_IsString(text) && cJSON_IsNumber(date) && cJSON_IsNumber(sender_color);
}

// Function to create a message from JSON data
t_msg *get_msg_from_json(cJSON *json)
{
    if (!json) {
        return NULL;
    }

    // Declare cJSON pointers for message attributes
    cJSON *msg_id, *sender_id, *sender_name, *sender_color, *text, *chat_id, *date;

    // Extract message attributes from JSON object
    extract_message_attributes(json, &msg_id, &sender_id, &sender_name, &sender_color, &text, &chat_id, &date);


    // Check if all required attributes are present and of the correct type
    if (!are_message_attributes_valid(msg_id, sender_id, chat_id, sender_name, text, date, sender_color))
    {
        return NULL;
    }

    // Create and return the message object
    return mx_create_msg(msg_id->valueint, sender_id->valueint, sender_name->valuestring, chat_id->valueint,
                         text->valuestring, get_string_time(date->valueint), sender_color->valueint);
}
