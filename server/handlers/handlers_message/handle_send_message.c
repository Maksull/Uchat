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

// Function to insert a message into the database and handle errors
static int insert_message_into_database(const cJSON *message_info, int *message_id, t_server_utils *utils)
{
    t_response_code resp_code = db_insert_message(message_info, message_id);
    if (resp_code != R_SUCCESS)
    {
        send_server_response(utils->ssl, resp_code, REQ_SEND_MESSAGE);

        return 1; // Error
    }

    return 0; // Success
}

// Function to create and send the response JSON object
static void send_response_json(int message_id, t_server_utils *utils)
{
    cJSON *json_to_send = cJSON_CreateObject();
    cJSON_AddNumberToObject(json_to_send, "message_id", message_id);
    cJSON_AddNumberToObject(json_to_send, "type", REQ_SEND_MESSAGE);
    cJSON_AddNumberToObject(json_to_send, "error_code", R_SUCCESS);

    char *json_str = cJSON_PrintUnformatted(json_to_send);
    cJSON_Delete(json_to_send);

    send_response_to(utils->ssl, json_str);

    free(json_str);
}

// Function to handle the sending of a message
void handle_send_message(const cJSON *message_info, t_server_utils *utils)
{
    // Initialize the database and check for initialization errors
    if (initialize_database(utils, REQ_SEND_MESSAGE) != 0)
    {
        return;
    }

    int message_id = 0;

    // Insert the message into the database and check for insertion errors
    if (insert_message_into_database(message_info, &message_id, utils) != 0)
    {
        return;
    }

    // Send the response JSON object
    send_response_json(message_id, utils);
}