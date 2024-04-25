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

// Function to extract chat name from the JSON object and validate it
static int extract_and_validate_chat_name(const cJSON *chat_info, const cJSON **chat_name, t_server_utils *utils)
{
    *chat_name = cJSON_GetObjectItemCaseSensitive(chat_info, "name");

    // Validate chat name
    if (!cJSON_IsString(*chat_name))
    {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_DELETE_CHAT); // Send response indicating JSON failure

        return 1;                                                          // Error
    }

    return 0; // Success
}

// Function to check if the user is a member of the chat and has admin permissions
static int check_user_permissions(const cJSON *chat_name, int *chat_id, t_server_utils *utils)
{
    // Get chat ID from database
    *chat_id = db_get_chat_id_by_name(chat_name->valuestring);

    // Check if the user is a member of the chat
    if (!db_is_chat_member(utils->user->user_id, *chat_id))
    {
        send_server_response(utils->ssl, R_ISNT_CHAT_MEMBER, REQ_DELETE_CHAT); // Send response indicating user is not a member of the chat

        return 1;                                                              // Error
    }

    // Check if the user has admin permissions for the chat
    if (!db_has_chat_perms(utils->user->user_id, *chat_id, ADMIN_MEMBER))
    {
        send_server_response(utils->ssl, R_NO_CHAT_PERMS, REQ_DELETE_CHAT); // Send response indicating user does not have permissions to delete the chat

        return 1;                                                           // Error
    }

    return 0; // Success
}

// Function to delete the chat, its members, and messages
static int delete_chat(int chat_id, const cJSON *chat_name, t_server_utils *utils)
{
    // Delete the chat
    t_response_code resp_code = db_delete_chat(chat_name->valuestring, chat_id);
    if (resp_code != R_SUCCESS)
    {
        send_server_response(utils->ssl, resp_code, REQ_DELETE_CHAT); // Send response indicating chat deletion failure

        return 1;                                                     // Error
    }

    // Delete chat members
    if (db_delete_members(chat_id) != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_DELETE_CHAT); // Send response indicating member deletion failure

        return 1;                                                        // Error
    }

    // Delete chat messages
    if (db_delete_messages(chat_id) != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_DELETE_CHAT); // Send response indicating message deletion failure

        return 1;                                                        // Error
    }

    return 0; // Success
}

// Function to handle the deletion of a chat
void handle_delete_chat(const cJSON *chat_info, t_server_utils *utils)
{
    // Initialize the database if not already initialized
    if (initialize_database(utils, REQ_DELETE_CHAT) != 0)
    {
        return;
    }

    const cJSON *chat_name;
    int chat_id;

    // Extract and validate chat name
    if (extract_and_validate_chat_name(chat_info, &chat_name, utils) != 0)
    {
        return;
    }

    // Check user permissions for the chat
    if (check_user_permissions(chat_name, &chat_id, utils) != 0)
    {
        return;
    }

    // Delete the chat, its members, and messages
    if (delete_chat(chat_id, chat_name, utils) != 0)
    {
        return;
    }

    // Send success response
    send_server_response(utils->ssl, R_SUCCESS, REQ_DELETE_CHAT);
}
