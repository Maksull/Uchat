#include "../../inc/server.h"

// Handle the deletion of a chat
void handle_delete_chat(const cJSON *chat_info, t_server_utils *utils)
{
    // Initialize the database if not already initialized
    if (init_db() != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_DELETE_CHAT); // Send response indicating database failure
        return;
    }

    // Extract chat name from JSON object
    const cJSON *chat_name = cJSON_GetObjectItemCaseSensitive(chat_info, "name");

    // Validate chat name
    if (!cJSON_IsString(chat_name))
    {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_DELETE_CHAT); // Send response indicating JSON failure
        return;
    }

    // Get chat ID from database
    int chat_id = db_get_chat_id_by_name(chat_name->valuestring);

    // Check if the user is a member of the chat
    if (!db_is_chat_member(utils->user->user_id, chat_id))
    {
        send_server_response(utils->ssl, R_ISNT_CHAT_MEMBER, REQ_DELETE_CHAT); // Send response indicating user is not a member of the chat
        return;
    }

    // Check if the user has admin permissions for the chat
    if (!db_has_chat_perms(utils->user->user_id, chat_id, ADMIN_MEMBER))
    {
        send_server_response(utils->ssl, R_NO_CHAT_PERMS, REQ_DELETE_CHAT); // Send response indicating user does not have permissions to delete the chat
        return;
    }

    // Delete the chat
    t_response_code resp_code = 0;
    if ((resp_code = db_delete_chat(chat_name->valuestring, chat_id)) != R_SUCCESS)
    {
        send_server_response(utils->ssl, resp_code, REQ_DELETE_CHAT); // Send response indicating chat deletion failure
        return;
    }

    // Delete chat members
    if (db_delete_members(chat_id) != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_DELETE_CHAT); // Send response indicating member deletion failure
        return;
    }

    // Delete chat messages
    if (db_delete_messages(chat_id) != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_DELETE_CHAT); // Send response indicating message deletion failure
        return;
    }

    // Send success response
    send_server_response(utils->ssl, R_SUCCESS, REQ_DELETE_CHAT);
}
