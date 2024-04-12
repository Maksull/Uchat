#include "../../inc/server.h"

// Function to initialize the database and handle initialization errors
int initialize_database(t_server_utils *utils, t_request_type request_type)
{
    if (init_db() != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, request_type);

        return 1; // Error
    }

    return 0; // Success
}

// Function to retrieve the chat ID corresponding to the chat name
int get_chat_id_by_name(const cJSON *chat_name, t_server_utils *utils)
{
    return db_get_chat_id_by_name(chat_name->valuestring);
}

// Function to attempt to delete the user as a member of the chat
int delete_user_as_member(int user_id, int chat_id, t_server_utils *utils)
{
    return db_delete_member(user_id, chat_id);
}

// Function to handle the request to leave a chat
void handle_leave_chat(const cJSON *chat_info, t_server_utils *utils)
{
    // Initialize the database if not already initialized
    if (initialize_database(utils, REQ_LEAVE_CHAT) != 0)
    {
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
    int chat_id = get_chat_id_by_name(chat_name, utils);
    if (chat_id == -1)
    {
        send_server_response(utils->ssl, R_CHAT_NOENT, REQ_LEAVE_CHAT); // Send response indicating chat does not exist
        return;
    }

    // Attempt to delete the user as a member of the chat
    int error_code = delete_user_as_member(utils->user->user_id, chat_id, utils);

    // Send response based on the result of deleting the user as a member
    send_server_response(utils->ssl, error_code == 0 ? R_SUCCESS : error_code, REQ_LEAVE_CHAT);
}
