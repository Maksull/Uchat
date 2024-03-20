#include "../../inc/client.h"

// Function to set current user details from a JSON object
void set_current_user(t_user **user, const cJSON *user_json)
{
    // Extracting relevant fields from the JSON object
    const cJSON *id_json = cJSON_GetObjectItem(user_json, "id");
    const cJSON *name_json = cJSON_GetObjectItemCaseSensitive(user_json, "username");
    const cJSON *pass_json = cJSON_GetObjectItemCaseSensitive(user_json, "password");
    const cJSON *color_json = cJSON_GetObjectItem(user_json, "avatar_color");

    // Checking if any required field is missing or has invalid data
    if (!cJSON_IsNumber(id_json) || !cJSON_IsString(name_json) ||
        !cJSON_IsString(pass_json) || !cJSON_IsNumber(color_json))
    {
        // If any required field is missing or has invalid data, return without setting user
        return;
    }

    // Allocating memory for the user structure
    *user = malloc(sizeof(t_user));

    // Assigning values to the user structure fields from JSON data
    (*user)->user_id = id_json->valueint;
    (*user)->name = mx_strdup(name_json->valuestring);
    (*user)->password = mx_strdup(pass_json->valuestring);
    (*user)->avatar_color = color_json->valueint;
    (*user)->avatar_path = NULL; // Assuming avatar_path is not provided in JSON, setting it to NULL
}
