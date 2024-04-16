#include "../../inc/client.h"

// Function to create a JSON object for logout request
cJSON *create_logout_json(bool is_client_exit) {
    // Create JSON object for the request
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", REQ_USR_LOGOUT);
    cJSON_AddNumberToObject(json, "client_exit", is_client_exit);

    return json;
}
