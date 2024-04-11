#include "../../inc/server.h"

// Function to delete user messages from the database
static int delete_user_messages(t_server_utils *utils)
{
    int error_code = 0;

    // Delete messages associated with the user
    if ((error_code = db_delete_messages(utils->user->user_id)) != R_SUCCESS)
    {
        send_server_response(utils->ssl, error_code, REQ_DELETE_ACCOUNT);
        return error_code;
    }

    return R_SUCCESS;
}

// Function to delete user account from the database
static int delete_user_account(t_server_utils *utils)
{
    int error_code = 0;

    // Delete the user from the 'users' table
    if ((error_code = db_delete_user(utils->user->user_id)) != R_SUCCESS)
    {
        send_server_response(utils->ssl, error_code, REQ_DELETE_ACCOUNT);
        return error_code;
    }

    // Delete the user from the 'members' table
    if ((error_code = db_delete_member_by_user_id(utils->user->user_id)) != R_SUCCESS)
    {
        send_server_response(utils->ssl, error_code, REQ_DELETE_ACCOUNT);
        return error_code;
    }

    // Attempt to delete user messages
    return delete_user_messages(utils);
}

// Function to handle account deletion
void handle_delete_account(const cJSON *chat_info, t_server_utils *utils)
{
    // Ignore chat_info parameter
    (void)chat_info;

    // Initialize the database
    if (init_db() != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_DELETE_ACCOUNT);
        return;
    }

    // Attempt to delete user account
    if (delete_user_account(utils) != R_SUCCESS)
    {
        client_cleanup(utils, false);
        return;
    }

    // Send success response
    send_server_response(utils->ssl, R_SUCCESS, REQ_DELETE_ACCOUNT);

    // Log the deletion
    logger("User has been removed\n", INFO_LOG);

    // Clean up resources associated with the client
    client_cleanup(utils, false);
}
