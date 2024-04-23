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

// Function to edit the message in the database and handle errors
static int edit_message_in_database(const cJSON *message_info, t_server_utils *utils, t_request_type request_type)
{
    t_response_code resp_code = 0;
    if ((resp_code = db_edit_message(message_info, utils)) != R_SUCCESS)
    {
        send_server_response(utils->ssl, resp_code, request_type);

        return 1; // Error
    }

    return 0; // Success
}

// Function to handle message editing
void handle_edit_message(const cJSON *message_info, t_server_utils *utils)
{
    // Initialize the database and check for initialization errors
    if (initialize_database(utils, REQ_EDIT_MESSAGE) != 0)
    {
        return;
    }

    // Edit the message in the database and check for errors
    if (edit_message_in_database(message_info, utils, REQ_EDIT_MESSAGE) != 0)
    {
        return;
    }

    // Send success response
    send_server_response(utils->ssl, R_SUCCESS, REQ_EDIT_MESSAGE);
}
