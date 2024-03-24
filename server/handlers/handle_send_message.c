#include "../inc/server.h"

// Function to handle the sending of a message
void handle_send_message(const cJSON *message_info, t_server_utils *utils)
{
    // Initialize the database and check for initialization errors
    if (init_database() != 0)
    {
        // If initialization fails, send a server response with the database failure code
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_SEND_MESSAGE);
        return;
    }

    // Declare variables to store response code and message ID
    t_response_code resp_code = 0;
    int message_id = 0;

    // Insert the message into the database and check for insertion errors
    if ((resp_code = db_insert_message(message_info, &message_id)) != R_SUCCESS)
    {
        // If insertion fails, send a server response with the corresponding error code
        send_server_response(utils->ssl, resp_code, REQ_SEND_MESSAGE);
        return;
    }

    // Create a JSON object to send as a response
    cJSON *json_to_send = cJSON_CreateObject();
    cJSON_AddNumberToObject(json_to_send, "message_id", message_id);
    cJSON_AddNumberToObject(json_to_send, "type", REQ_SEND_MESSAGE);
    cJSON_AddNumberToObject(json_to_send, "error_code", R_SUCCESS);

    // Convert the JSON object to a string
    char *json_str = cJSON_PrintUnformatted(json_to_send);
    cJSON_Delete(json_to_send);

    // Send the JSON response to the client
    send_response_to(utils->ssl, json_str);

    // Free the memory allocated for the JSON string
    free(json_str);
}
