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

// Function to retrieve chats associated with the user
cJSON *retrieve_user_chats(t_server_utils *utils)
{
    return db_get_chats_by_user_id(utils->user->user_id);
}

// Function to create and send the response JSON object
void send_response_json(cJSON *chats, t_server_utils *utils, t_request_type request_type)
{
    cJSON *json = cJSON_CreateObject();
    cJSON_AddItemReferenceToObject(json, "chats", chats);
    cJSON_AddNumberToObject(json, "type", request_type);
    cJSON_AddNumberToObject(json, "error_code", R_SUCCESS);

    char *json_str = cJSON_PrintUnformatted(json);
    send_response_to(utils->ssl, json_str);

    cJSON_Delete(json);
    free(json_str);
}

// Function to handle the retrieval of chats for a user
void handle_get_chats(const cJSON *chat_info, t_server_utils *utils)
{
    // Ignore chat_info parameter
    (void)chat_info;

    // Initialize the database if not already initialized
    if (initialize_database(utils, REQ_GET_CHATS) != 0)
    {
        return;
    }

    // Retrieve chats associated with the user
    cJSON *chats = retrieve_user_chats(utils);
    if (chats == NULL)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_GET_CHATS); // Send response indicating database failure
        return;
    }

    // Send the response JSON object
    send_response_json(chats, utils, REQ_GET_CHATS);
    cJSON_Delete(chats);
}
