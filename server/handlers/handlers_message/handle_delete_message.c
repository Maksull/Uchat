#include "../../inc/server.h"

// Function to handle the deletion of a message
void handle_delete_message(const cJSON *message_info, t_server_utils *utils)
{
    // Initialize the database and check for initialization errors
    if (init_database() != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_DELETE_MESSAGE);
        return;
    }

    t_response_code resp_code = 0;

    // Delete the message from the database and check for errors
    if ((resp_code = db_delete_message(message_info, utils)) != R_SUCCESS)
    {
        send_server_response(utils->ssl, resp_code, REQ_DELETE_MESSAGE);
        return;
    }

    // Send a success response to the client
    send_server_response(utils->ssl, R_SUCCESS, REQ_DELETE_MESSAGE);
}
