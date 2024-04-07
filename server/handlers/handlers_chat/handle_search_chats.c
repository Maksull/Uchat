#include "../../inc/server.h"

// Handle the request to search for chats
void handle_search_chats(const cJSON *chat_info, t_server_utils *utils)
{
    // Initialize the database if not already initialized
    if (init_db() != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_SEARCH_CHATS); // Send response indicating database failure
        return;
    }

    // Create a JSON object
    cJSON *json = cJSON_CreateObject();

    // Get the search results for chats based on the provided information
    cJSON *chats = db_get_search_chats(chat_info, utils);

    // Add the search results to the JSON object
    cJSON_AddItemReferenceToObject(json, "chats", chats);
    cJSON_AddNumberToObject(json, "type", REQ_SEARCH_CHATS);
    cJSON_AddNumberToObject(json, "error_code", R_SUCCESS);

    // Convert the JSON object to string
    char *json_str = cJSON_PrintUnformatted(json);

    // Send the JSON string as a response to the client
    send_response_to(utils->ssl, json_str);

    // Clean up memory
    cJSON_Delete(json);
    free(json_str);
}
