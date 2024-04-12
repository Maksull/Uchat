#include "../../inc/server.h"

// Function to initialize the database and handle initialization errors
static int initialize_database(t_server_utils *utils)
{
    if (init_db() != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_DELETE_MESSAGE);
        return 1; // Error
    }

    return 0; // Success
}

// Function to delete the message from the database and handle errors
static int delete_message_from_database(const cJSON *message_info, t_server_utils *utils)
{
    t_response_code resp_code = 0;
    if ((resp_code = db_delete_message(message_info, utils)) != R_SUCCESS)
    {
        send_server_response(utils->ssl, resp_code, REQ_DELETE_MESSAGE);
        return 1; // Error
    }

    return 0; // Success
}

// Function to handle the deletion of a message
void handle_delete_message(const cJSON *message_info, t_server_utils *utils)
{
    // Initialize the database and check for initialization errors
    if (initialize_database(utils) != 0)
    {
        return;
    }

    // Delete the message from the database and check for errors
    if (delete_message_from_database(message_info, utils) != 0)
    {
        return;
    }

    // Send a success response to the client
    send_server_response(utils->ssl, R_SUCCESS, REQ_DELETE_MESSAGE);
}
