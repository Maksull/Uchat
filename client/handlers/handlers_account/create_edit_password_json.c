#include "../../inc/client.h"

// Function to create a JSON object for edit password request
cJSON *create_edit_password_json(const char *new_pass, const char *old_pass) {
    // Create JSON object for the request
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "new_password", new_pass);
    cJSON_AddStringToObject(json, "old_password", old_pass);
    cJSON_AddNumberToObject(json, "type", REQ_EDIT_PASSWORD);

    return json;
}
