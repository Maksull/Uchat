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

// Function to retrieve the ID of the last message in a chat and handle errors
static int retrieve_last_message_id(const cJSON *chat_info, int *last_msg_id, t_server_utils *utils)
{
    int error_code = db_get_last_message_id(chat_info, last_msg_id);
    if (error_code != R_SUCCESS)
    {
        send_server_response(utils->ssl, error_code, REQ_LAST_MSG_ID);

        return 1; // Error
    }
    
    return 0; // Success
}

// Function to create and send the response JSON object
static void send_response_json(int last_msg_id, t_server_utils *utils)
{
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "last_msg_id", last_msg_id);
    cJSON_AddNumberToObject(json, "type", REQ_LAST_MSG_ID);
    cJSON_AddNumberToObject(json, "error_code", R_SUCCESS);

    char *json_str = cJSON_PrintUnformatted(json);
    send_response_to(utils->ssl, json_str);
    cJSON_Delete(json);
    free(json_str);
}

// Function to handle the retrieval of the ID of the last message in a chat
void handle_last_msg_id(const cJSON *chat_info, t_server_utils *utils)
{
    // Initialize the database and check for initialization errors
    if (initialize_database(utils, REQ_LAST_MSG_ID) != 0)
    {
        return;
    }

    int last_msg_id = -1;

    // Retrieve the last message ID and check for errors
    if (retrieve_last_message_id(chat_info, &last_msg_id, utils) != 0)
    {
        return;
    }

    // Send the response JSON object
    send_response_json(last_msg_id, utils);
}
