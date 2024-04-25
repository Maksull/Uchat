#include "../../inc/client.h"

// Function to create a JSON object for logout request
static cJSON *create_logout_json(bool is_client_exit)
{
    // Create JSON object for the request
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", REQ_USR_LOGOUT);
    cJSON_AddNumberToObject(json, "client_exit", is_client_exit);

    return json;
}

// Function to handle logout request
void handle_logout_req(bool is_client_exit)
{
    // Suspend operations
    utils->is_suspended = true;

    // Create JSON object for logout request
    cJSON *json = create_logout_json(is_client_exit);
    char *json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    // Send logout request to server
    send_to_server(utils->ssl, json_str);

    // Free allocated memory
    free(json_str);
}
