#include "../../inc/server.h"

// Handle the retrieval of chats for a user
void handle_get_chats(const cJSON *chat_info, t_server_utils *utils)
{
    // Ignore chat_info parameter
    (void)chat_info;

    // Initialize the database if not already initialized
    if (init_db() != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_GET_CHATS); // Send response indicating database failure
        return;
    }

    // Create a JSON object
    cJSON *json = cJSON_CreateObject();

    // Get the chats associated with the user
    cJSON *chats = db_get_chats_by_user_id(utils->user->user_id);

    // Add chats array to JSON object
    cJSON_AddItemReferenceToObject(json, "chats", chats);

    // Add type and error_code fields to JSON object
    cJSON_AddNumberToObject(json, "type", REQ_GET_CHATS);
    cJSON_AddNumberToObject(json, "error_code", R_SUCCESS);

    // Convert JSON object to string
    char *json_str = cJSON_PrintUnformatted(json);

    // Send the JSON string as response
    send_response_to(utils->ssl, json_str);

    // Clean up resources
    cJSON_Delete(chats);
    cJSON_Delete(json);
    free(json_str);
}
