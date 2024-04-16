#include "../../inc/client.h"

// Function to create a JSON object for signup request
cJSON *create_signup_json(const char *user_name, const char *user_password) {
    // Create JSON object for the request
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "name", user_name);
    cJSON_AddStringToObject(json, "password", user_password);
    cJSON_AddNumberToObject(json, "avatar_color", get_avatar_color());
    cJSON_AddNumberToObject(json, "type", REQ_USR_SIGNUP);

    return json;
}
