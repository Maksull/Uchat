#include "../../inc/server.h"

// Function to handle the editing of a message
void handle_edit_message(const cJSON *message_info, t_server_utils *utils)
{
    // Initialize the database and check for initialization errors
    if (init_database() != 0)
    {
        // If initialization fails, send a server response with the database failure code
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_EDIT_MESSAGE);
        return;
    }

    // Declare a variable to store the response code
    t_response_code resp_code = 0;

    // Edit the message in the database and check for errors
    if ((resp_code = db_edit_message(message_info, utils) != R_SUCCESS))
    {
        // If editing fails, send a server response with the corresponding error code
        send_server_response(utils->ssl, resp_code, REQ_EDIT_MESSAGE);
        return;
    }

    // Send a success response to the client
    send_server_response(utils->ssl, R_SUCCESS, REQ_EDIT_MESSAGE);
}
