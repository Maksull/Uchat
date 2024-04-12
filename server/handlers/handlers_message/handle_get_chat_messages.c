#include "../../inc/server.h"

// Function to initialize the database and handle initialization errors
static int initialize_database(t_server_utils *utils, t_request_type request_type)
{
    if (init_db() != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, request_type);
        return 1; // Error
    }
    return 0; // Success
}

// Function to check if chat_id is a number and handle errors
static int validate_chat_id(const cJSON *chat_info, t_server_utils *utils)
{
    const cJSON *chat_id = cJSON_GetObjectItemCaseSensitive(chat_info, "chat_id");
    if (!cJSON_IsNumber(chat_id))
    {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_GET_CHAT_MSGS);

        return 1; // Error
    }

    return 0; // Success
}

// Function to check if the chat exists in the database and handle errors
static int check_chat_exists(const cJSON *chat_info, t_server_utils *utils)
{
    const cJSON *chat_id = cJSON_GetObjectItemCaseSensitive(chat_info, "chat_id");
    if (!db_chat_exists(chat_id->valueint))
    {
        send_server_response(utils->ssl, R_CHAT_NOENT, REQ_GET_CHAT_MSGS);

        return 1; // Error
    }

    return 0; // Success
}

// Function to check if the user is a member of the chat and handle errors
static int check_user_membership(const cJSON *chat_info, t_server_utils *utils)
{
    const cJSON *chat_id = cJSON_GetObjectItemCaseSensitive(chat_info, "chat_id");
    if (!db_is_chat_member(utils->user->user_id, chat_id->valueint))
    {
        send_server_response(utils->ssl, R_ISNT_CHAT_MEMBER, REQ_GET_CHAT_MSGS);

        return 1; // Error
    }
    
    return 0; // Success
}

// Function to retrieve messages for a chat and handle errors
void retrieve_chat_messages(const cJSON *chat_info, t_server_utils *utils)
{
    cJSON *json = cJSON_CreateObject();
    const cJSON *chat_id = cJSON_GetObjectItemCaseSensitive(chat_info, "chat_id");
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

// Function to handle the retrieval of messages for a chat
void handle_get_chat_msgs(const cJSON *chat_info, t_server_utils *utils)
{
    // Initialize the database and check for initialization errors
    if (initialize_database(utils, REQ_GET_CHAT_MSGS) != 0)
    {
        return;
    }

    // Check if chat_id is a number
    if (validate_chat_id(chat_info, utils) != 0)
    {
        return;
    }

    // Check if the chat exists in the database
    if (check_chat_exists(chat_info, utils) != 0)
    {
        return;
    }

    // Check if the user is a member of the chat
    if (check_user_membership(chat_info, utils) != 0)
    {
        return;
    }

    // Retrieve messages for the chat
    retrieve_chat_messages(chat_info, utils);
}
