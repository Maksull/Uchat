#include "../../inc/server.h"

// Handle the request to join a chat
void handle_join_chat(const cJSON *chat_info, t_server_utils *utils)
{
    // Initialize the database if not already initialized
    if (init_db() != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_JOIN_CHAT); // Send response indicating database failure
        return;
    }

    // Retrieve the chat_name from the JSON object
    const cJSON *chat_name = cJSON_GetObjectItemCaseSensitive(chat_info, "chat_name");

    // Check if chat_name is a string
    if (!cJSON_IsString(chat_name))
    {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_JOIN_CHAT); // Send response indicating JSON failure
        return;
    }

    // Get the chat_id corresponding to the chat_name
    int chat_id = db_get_chat_id_by_name(chat_name->valuestring);

    // Check if the chat exists
    if (chat_id == -1)
    {
        send_server_response(utils->ssl, R_CHAT_NOENT, REQ_JOIN_CHAT); // Send response indicating chat does not exist
        return;
    }

    // Check if the user is already a member of the chat
    if (db_is_chat_member(utils->user->user_id, chat_id))
    {
        send_server_response(utils->ssl, R_IS_CHAT_MEMBER, REQ_JOIN_CHAT); // Send response indicating user is already a member
        return;
    }

    // Check if the user has reached the maximum limit of chats
    if (db_get_chats_total(utils->user->user_id) >= MAX_CHATS_TOTAL)
    {
        send_server_response(utils->ssl, R_CHATS_TOTAL_REACHED, REQ_JOIN_CHAT); // Send response indicating maximum chats reached
        return;
    }

    // Attempt to insert the user as a member of the chat
    t_response_code resp_code = db_insert_member(chat_name->valuestring, NORMAL_MEMBER, utils);

    if (resp_code != R_SUCCESS)
    {
        send_server_response(utils->ssl, resp_code, REQ_JOIN_CHAT);
        return;
    }

    send_server_response(utils->ssl, R_SUCCESS, REQ_JOIN_CHAT);
}
