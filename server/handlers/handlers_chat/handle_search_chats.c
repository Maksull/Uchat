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

// Function to retrieve search results for chats based on the provided information
cJSON *retrieve_chat_search_results(const cJSON *chat_info, t_server_utils *utils)
{
    return db_get_search_chats(chat_info, utils);
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

// Function to handle the request to search for chats
void handle_search_chats(const cJSON *chat_info, t_server_utils *utils)
{
    // Initialize the database if not already initialized
    if (initialize_database(utils, REQ_SEARCH_CHATS) != 0)
    {
        return;
    }

    // Retrieve search results for chats based on the provided information
    cJSON *chats = retrieve_chat_search_results(chat_info, utils);
    if (chats == NULL)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_SEARCH_CHATS); // Send response indicating database failure
        return;
    }

    // Send the response JSON object
    send_response_json(chats, utils, REQ_SEARCH_CHATS);
    cJSON_Delete(chats);
}
