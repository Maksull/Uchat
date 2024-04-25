#include "../../inc/server.h"

// Function to initialize the database and handle initialization errors
int initialize_database(t_server_utils *utils, t_request_type request_type)
{
    if (init_db() != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, request_type);

        return 1; // Error
    }

    return 0; // Success
}

// Function to retrieve a message by ID from the database and handle errors
cJSON *retrieve_message_by_id(const cJSON *msg_info, t_server_utils *utils)
{
    cJSON *msg_json = db_get_message_by_id(msg_info);
    if (msg_json == NULL)
    {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_GET_MSG);

        return NULL; // Error
    }

    return msg_json; // Success
}

// Function to create and send the response JSON object
void send_response_json(cJSON *msg_json, t_server_utils *utils, t_request_type request_type)
{
    cJSON *json = cJSON_CreateObject();
    cJSON_AddItemReferenceToObject(json, "message", msg_json);
    cJSON_AddNumberToObject(json, "type", request_type);
    cJSON_AddNumberToObject(json, "error_code", R_SUCCESS);

    char *json_str = cJSON_PrintUnformatted(json);
    send_response_to(utils->ssl, json_str);
    cJSON_Delete(json);
    free(json_str);
}

// Function to handle the retrieval of a message
void handle_get_msg(const cJSON *msg_info, t_server_utils *utils)
{
    // Initialize the database and check for initialization errors
    if (initialize_database(utils, REQ_GET_MSG) != 0)
    {
        return;
    }

    // Retrieve the message by ID from the database and handle errors
    cJSON *msg_json = retrieve_message_by_id(msg_info, utils);
    if (msg_json == NULL)
    {
        return;
    }

    // Send the response JSON object
    send_response_json(msg_json, utils, REQ_GET_MSG);
}
