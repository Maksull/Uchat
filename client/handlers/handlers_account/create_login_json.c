#include "../../inc/client.h"

// Function to create a JSON object for login request
cJSON *create_login_json(const char *user_name, const char *user_password) {
    // Create JSON object for the request
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "name", user_name);
    cJSON_AddStringToObject(json, "password", user_password);
    cJSON_AddNumberToObject(json, "type", REQ_USR_LOGIN);

    return json;
}
