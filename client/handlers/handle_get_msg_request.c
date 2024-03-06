#include "../inc/client.h"

// Handle request to get a message
void handle_get_msg_request(int chat_id, int message_id)
{
    // Create a JSON object
    cJSON *json = cJSON_CreateObject();
    // Add request type, message ID, and chat ID to the JSON object
    cJSON_AddNumberToObject(json, "type", REQ_GET_MSG);
    cJSON_AddNumberToObject(json, "message_id", message_id);
    cJSON_AddNumberToObject(json, "chat_id", chat_id);
    // Convert JSON object to string
    char *json_str = cJSON_PrintUnformatted(json);
    // Delete JSON object to free memory
    cJSON_Delete(json);
    // Send JSON string to the server
    send_to_server(utils->ssl, json_str);
    // Free memory allocated for JSON string
    free(json_str);
}
