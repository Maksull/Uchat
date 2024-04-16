#include "../../inc/client.h"

// Function to create a JSON object for edit username request
cJSON *create_edit_username_json(const char *new_name) {
    // Create JSON object for the request
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "name", new_name);
    cJSON_AddNumberToObject(json, "type", REQ_EDIT_USERNAME);

    return json;
}
