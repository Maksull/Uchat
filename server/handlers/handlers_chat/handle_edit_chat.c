#include "../../inc/server.h"

// Handle the editing of a chat
void handle_edit_chat(const cJSON *chat_info, t_server_utils *utils)
{
    // Initialize the database if not already initialized
    if (init_db() != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_EDIT_CHAT); // Send response indicating database failure
        return;
    }

    // Extract chat ID and new name from JSON object
    const cJSON *chat_id = cJSON_GetObjectItemCaseSensitive(chat_info, "chat_id");
    const cJSON *new_name = cJSON_GetObjectItemCaseSensitive(chat_info, "chat_name");

    // Validate new name and chat ID
    if (!cJSON_IsString(new_name) || !cJSON_IsNumber(chat_id))
    {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_EDIT_CHAT); // Send response indicating JSON failure
        return;
    }

    // Check if the chat exists
    if (!db_chat_exists(chat_id->valueint))
    {
        send_server_response(utils->ssl, R_CHAT_NOENT, REQ_EDIT_CHAT); // Send response indicating chat does not exist
        return;
    }

    // Validate the new name length
    if (!is_strlen_valid(new_name->valuestring, MIN_NAME_INPUT_LEN, MAX_NAME_INPUT_LEN))
    {
        send_server_response(utils->ssl, R_NAME_LEN_INVALID, REQ_EDIT_CHAT); // Send response indicating invalid name length
        return;
    }

    // Validate the new name format
    if (!is_user_name_format_valid(new_name->valuestring))
    {
        send_server_response(utils->ssl, R_NAME_FORMAT_INVALID, REQ_EDIT_CHAT); // Send response indicating invalid name format
        return;
    }

    // Modify the chat name
    t_response_code resp_code = 0;
    if ((resp_code = db_modify_chat_name(chat_id->valueint, new_name->valuestring)) != R_SUCCESS)
    {
        send_server_response(utils->ssl, resp_code, REQ_EDIT_CHAT); // Send response indicating chat modification failure
        return;
    }

    // Send success response
    send_server_response(utils->ssl, R_SUCCESS, REQ_EDIT_CHAT);
}
