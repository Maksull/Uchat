#include "../../inc/server.h"

// Function to handle the retrieval of messages for a chat
void handle_get_chat_msgs(const cJSON *chat_info, t_server_utils *utils)
{
    // Initialize the database and check for initialization errors
    if (init_db() != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_GET_CHAT_MSGS);
        return;
    }

    const cJSON *chat_id = cJSON_GetObjectItemCaseSensitive(chat_info, "chat_id");

    // Check if chat_id is a number
    if (!cJSON_IsNumber(chat_id))
    {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_GET_CHAT_MSGS);
        return;
    }

    // Check if the chat exists in the database
    if (!db_chat_exists(chat_id->valueint))
    {
        send_server_response(utils->ssl, R_CHAT_NOENT, REQ_GET_CHAT_MSGS);
        return;
    }

    // Check if the user is a member of the chat
    if (!db_is_chat_member(utils->user->user_id, chat_id->valueint))
    {
        send_server_response(utils->ssl, R_ISNT_CHAT_MEMBER, REQ_GET_CHAT_MSGS);
        return;
    }

    cJSON *json = cJSON_CreateObject();
    cJSON *messages = db_get_messages_array_json(chat_id->valueint);
    cJSON_AddItemReferenceToObject(json, "messages", messages);

    // Add type, error_code fields to the JSON object
    cJSON_AddNumberToObject(json, "type", REQ_GET_CHAT_MSGS);
    cJSON_AddNumberToObject(json, "error_code", R_SUCCESS);

    char *json_str = cJSON_PrintUnformatted(json);
    send_response_to(utils->ssl, json_str);
    cJSON_Delete(messages);
    cJSON_Delete(json);
    free(json_str);
}
