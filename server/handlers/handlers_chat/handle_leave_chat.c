#include "../../inc/server.h"

// Handle the request to leave a chat
void handle_leave_chat(const cJSON *chat_info, t_server_utils *utils)
{
    // Initialize the database if not already initialized
    if (init_db() != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_LEAVE_CHAT); // Send response indicating database failure
        return;
    }

    // Retrieve the chat_name from the JSON object
    const cJSON *chat_name = cJSON_GetObjectItemCaseSensitive(chat_info, "name");

    // Check if chat_name is a string
    if (!cJSON_IsString(chat_name))
    {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_LEAVE_CHAT); // Send response indicating JSON failure
        return;
    }

    // Get the chat_id corresponding to the chat_name
    int chat_id = db_get_chat_id_by_name(chat_name->valuestring);

    // Attempt to delete the user as a member of the chat
    int error_code = db_delete_member(utils->user->user_id, chat_id);

    // Send response based on the result of deleting the user as a member
    send_server_response(utils->ssl, error_code == 0 ? R_SUCCESS : error_code, REQ_LEAVE_CHAT);
}
