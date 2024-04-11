#include "../../inc/server.h"

// Function to initialize the database for user signup
static int initialize_database_for_signup(t_server_utils *utils)
{
    if (init_db() != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_USR_SIGNUP);
        return R_DB_FAILURE;
    }
    return R_SUCCESS;
}

// Function to add user to the database
static int add_user_to_database(const cJSON *user_info)
{
    int error_code = db_add_user(user_info);
    return error_code;
}

// Handle user signup request
void handle_user_signup(const cJSON *user_info, t_server_utils *utils)
{
    // Initialize the database
    if (initialize_database_for_signup(utils) != R_SUCCESS)
    {
        return;
    }

    int error_code = 0;

    // Add user to the database
    int error_code = add_user_to_database(user_info);
    if (error_code != R_SUCCESS)
    {
        // If adding user to the database fails, send corresponding error response and return
        send_server_response(utils->ssl, error_code, REQ_USR_SIGNUP);
        return;
    }

    // Send success response for user signup
    send_server_response(utils->ssl, R_SUCCESS, REQ_USR_SIGNUP);
}
