#include "../inc/server.h"

// Handle user signup request
void handle_user_signup(const cJSON *user_info, t_server_utils *utils)
{
    // Initialize the database
    if (init_database() != 0)
    {
        // If database initialization fails, send database failure response and return
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_USR_SIGNUP);
        return;
    }

    int error_code = 0;

    // Add user to the database
    if ((error_code = db_add_user(user_info)) != R_SUCCESS)
    {
        // If adding user to the database fails, send corresponding error response and return
        send_server_response(utils->ssl, error_code, REQ_USR_SIGNUP);
        return;
    }

    // Send success response for user signup
    send_server_response(utils->ssl, R_SUCCESS, REQ_USR_SIGNUP);
}
