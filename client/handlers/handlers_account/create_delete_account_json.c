#include "../../inc/client.h"

// Function to create a JSON object for delete account request
cJSON *create_delete_account_json() {
    // Create JSON object for the request
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", REQ_DELETE_ACCOUNT);

    return json;
}
