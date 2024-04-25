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

// Function to retrieve the chat ID corresponding to the chat name
static int get_chat_id_by_name(const cJSON *chat_name)
{
    return db_get_chat_id_by_name(chat_name->valuestring);
}

// Function to check if the user is already a member of the chat
static int check_user_membership(int user_id, int chat_id, t_server_utils *utils)
{
    if (db_is_chat_member(user_id, chat_id))
    {
        send_server_response(utils->ssl, R_IS_CHAT_MEMBER, REQ_JOIN_CHAT); // Send response indicating user is already a member

        return 1;                                                          // Error
    }

    return 0; // Success
}

// Function to check if the user has reached the maximum limit of chats
static int check_max_chat_limit(int user_id, t_server_utils *utils)
{
    if (db_get_chats_total(user_id) >= MAX_CHATS_TOTAL)
    {
        send_server_response(utils->ssl, R_CHATS_TOTAL_REACHED, REQ_JOIN_CHAT); // Send response indicating maximum chats reached

        return 1;                                                               // Error
    }

    return 0; // Success
}

// Function to attempt to insert the user as a member of the chat
static int insert_user_as_member(const cJSON *chat_name, t_server_utils *utils)
{
    t_response_code resp_code = db_insert_member(chat_name->valuestring, NORMAL_MEMBER, utils);
    if (resp_code != R_SUCCESS)
    {
        send_server_response(utils->ssl, resp_code, REQ_JOIN_CHAT);

        return 1; // Error
    }

    return 0; // Success
}

// Function to handle the request to join a chat
void handle_join_chat(const cJSON *chat_info, t_server_utils *utils)
{
    // Initialize the database if not already initialized
    if (initialize_database(utils, REQ_JOIN_CHAT) != 0)
    {
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
    int chat_id = get_chat_id_by_name(chat_name);
    if (chat_id == -1)
    {
        send_server_response(utils->ssl, R_CHAT_NOENT, REQ_JOIN_CHAT); // Send response indicating chat does not exist
        
        return;
    }

    // Check if the user is already a member of the chat
    if (check_user_membership(utils->user->user_id, chat_id, utils) != 0)
    {
        return;
    }

    // Check if the user has reached the maximum limit of chats
    if (check_max_chat_limit(utils->user->user_id, utils) != 0)
    {
        return;
    }

    // Attempt to insert the user as a member of the chat
    if (insert_user_as_member(chat_name, utils) != 0)
    {
        return;
    }

    send_server_response(utils->ssl, R_SUCCESS, REQ_JOIN_CHAT);
}
