#include "../inc/server.h"

// Handle the creation of a new chat
void handle_create_chat(const cJSON *chat_info, t_server_utils *utils)
{
    // Initialize the database if not already initialized
    if (init_database() != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_CREATE_CHAT); // Send response indicating database failure
        return;
    }

    // Extract chat information from JSON object
    const cJSON *chat_name = cJSON_GetObjectItemCaseSensitive(chat_info, "name");
    const cJSON *date = cJSON_GetObjectItem(chat_info, "date");
    const cJSON *av_color = cJSON_GetObjectItem(chat_info, "avatar_color");

    // Validate chat information
    if (!cJSON_IsString(chat_name) || !cJSON_IsNumber(av_color) || !cJSON_IsNumber(date))
    {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_CREATE_CHAT); // Send response indicating JSON failure
        return;
    }

    // Validate chat name length and format
    if (!is_strlen_valid(chat_name->valuestring, MIN_NAME_INPUT_LEN, MAX_NAME_INPUT_LEN))
    {
        send_server_response(utils->ssl, R_NAME_LEN_INVALID, REQ_CREATE_CHAT); // Send response indicating invalid name length
        return;
    }

    if (!is_user_name_format_valid(chat_name->valuestring))
    {
        send_server_response(utils->ssl, R_NAME_FORMAT_INVALID, REQ_CREATE_CHAT); // Send response indicating invalid name format
        return;
    }

    // Check if maximum total chats limit reached
    if (db_get_chats_total(utils->user->user_id) >= MAX_CHATS_TOTAL)
    {
        send_server_response(utils->ssl, R_CHATS_TOTAL_REACHED, REQ_CREATE_CHAT); // Send response indicating maximum chats reached
        return;
    }

    // Insert new chat into the database
    t_response_code resp_code = 0;
    if ((resp_code = db_insert_chat(chat_name->valuestring, date->valueint, av_color->valueint)) != R_SUCCESS)
    {
        send_server_response(utils->ssl, resp_code, REQ_CREATE_CHAT); // Send response indicating chat insertion failure
        return;
    }

    // Insert the current user as an admin member of the chat
    if (db_insert_member(chat_name->valuestring, ADMIN_MEMBER, utils) != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_CREATE_CHAT); // Send response indicating member insertion failure
        return;
    }

    // Send success response
    send_server_response(utils->ssl, R_SUCCESS, REQ_CREATE_CHAT);
}
