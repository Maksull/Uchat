#include "../../inc/client.h"

// Handle request to get a message
void handle_get_msg_req(int chat_id, int message_id)
{
    // Create a JSON object
    cJSON *json = create_get_msg_json(chat_id, message_id);
    // Convert JSON object to string
    char *json_str = cJSON_PrintUnformatted(json);
    // Delete JSON object to free memory
    cJSON_Delete(json);
    // Send JSON string to the server
    send_to_server(utils->ssl, json_str);
    // Free memory allocated for JSON string
    free(json_str);
}
