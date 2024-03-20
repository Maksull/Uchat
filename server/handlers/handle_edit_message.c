#include "../inc/server.h"

// Function to handle message editing
void handle_edit_message(const cJSON *message_info, t_server_utils *utils)
{
    // Initialize the database
    if (init_database() != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_EDIT_MESSAGE);
        return;
    }

    // Response code for handling errors
    t_response_code resp_code = 0;

    // Edit the message in the database
    if ((resp_code = db_edit_message(message_info, utils)) != R_SUCCESS)
    {
        send_server_response(utils->ssl, resp_code, REQ_EDIT_MESSAGE);
        return;
    }

    // Send success response
    send_server_response(utils->ssl, R_SUCCESS, REQ_EDIT_MESSAGE);
}
