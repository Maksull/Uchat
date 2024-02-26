#include "../inc/server.h"

// Function to handle account deletion
void handle_delete_account(const cJSON *chat_info, t_server_utils *utils)
{
    // Ignore chat_info parameter
    (void)chat_info;

    // Initialize the database
    if (init_database() != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_DELETE_ACCOUNT);
        return;
    }

    int error_code = 0;

    // Delete the user from the 'users' table
    if ((error_code = db_delete_user(utils->user->user_id)) != R_SUCCESS)
    {
        send_server_response(utils->ssl, error_code, REQ_DELETE_ACCOUNT);
        return;
    }

    // Delete the user from the 'members' table
    if ((error_code = db_delete_member_by_user_id(utils->user->user_id)) != R_SUCCESS)
    {
        send_server_response(utils->ssl, error_code, REQ_DELETE_ACCOUNT);
        return;
    }

    // Delete messages associated with the user
    if ((error_code = db_delete_messages(utils->user->user_id)) != R_SUCCESS)
    {
        send_server_response(utils->ssl, error_code, REQ_DELETE_ACCOUNT);
        return;
    }

    // Send success response
    send_server_response(utils->ssl, R_SUCCESS, REQ_DELETE_ACCOUNT);

    // Log the deletion
    logger("User has been removed\n", INFO_LOG);

    // Clean up resources associated with the client
    client_cleanup(utils, false);
}
