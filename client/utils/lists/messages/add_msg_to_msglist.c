#include "../../../inc/client.h"

// Function to extract message information from JSON object
static void extract_msg_info(cJSON *json, cJSON **msg_id, cJSON **sender_id, cJSON **sender_name, cJSON **sender_color, cJSON **text, cJSON **chat_id, cJSON **date)
{
    // Extract message information from the JSON object
    *msg_id = cJSON_GetObjectItem(json, "msg_id");
    *sender_id = cJSON_GetObjectItem(json, "sender_id");
    *sender_name = cJSON_GetObjectItemCaseSensitive(json, "sender_name");
    *sender_color = cJSON_GetObjectItem(json, "sender_color");
    *text = cJSON_GetObjectItemCaseSensitive(json, "text");
    *chat_id = cJSON_GetObjectItem(json, "chat_id");
    *date = cJSON_GetObjectItemCaseSensitive(json, "date");
}

// Function to add a message to the message list
t_response_code add_msg_to_msglist(cJSON *json)
{
    if (!json)
    {
        return R_JSON_FAILURE;
    }

    cJSON *msg_id, *sender_id, *sender_name, *sender_color, *text, *chat_id, *date;
    // Extract message information from the JSON object
    extract_msg_info(json, &msg_id, &sender_id, &sender_name, &sender_color, &text, &chat_id, &date);

    // Check if the required fields are present and have the correct types
    if (!cJSON_IsNumber(msg_id) || !cJSON_IsNumber(sender_id) || !cJSON_IsNumber(chat_id) ||
        !cJSON_IsString(sender_name) || !cJSON_IsString(text) || !cJSON_IsNumber(date) || !cJSON_IsNumber(sender_color))
    {
        return R_JSON_FAILURE;
    }

    // Find the chat by its ID
    t_chat *chat_by_id = mx_get_chat_by_id(utils->chatlist, chat_id->valueint);
    if (!chat_by_id)
    {
        return R_CHAT_NOENT;
    }

    // Create a new message and add it to the chat's message list
    t_msg *new_msg = mx_create_msg(msg_id->valueint, sender_id->valueint, sender_name->valuestring, chat_id->valueint,
                                   text->valuestring, get_string_time(date->valueint), sender_color->valueint);

    mx_msg_push_back(&chat_by_id->messages, new_msg);

    // Update the last new message of the chat
    chat_by_id->last_new_msg = mx_get_last_msg_node(chat_by_id->messages);

    return R_SUCCESS;
}
