#include "../../inc/client.h"

// Function to extract user information from JSON object
static void extract_user_info(const cJSON *user_json, const cJSON **id_json, const cJSON **name_json, const cJSON **pass_json, const cJSON **color_json)
{
    // Extract relevant fields from the JSON object
    *id_json = cJSON_GetObjectItem(user_json, "id");
    *name_json = cJSON_GetObjectItemCaseSensitive(user_json, "username");
    *pass_json = cJSON_GetObjectItemCaseSensitive(user_json, "password");
    *color_json = cJSON_GetObjectItem(user_json, "avatar_color");
}

// Function to check if cJSON objects meet certain conditions
static int check_user_json(const cJSON *id_json, const cJSON *name_json, const cJSON *pass_json, const cJSON *color_json)
{
    // Check if any of the cJSON objects are not of the expected types
    if (!cJSON_IsNumber(id_json) || !cJSON_IsString(name_json) ||
        !cJSON_IsString(pass_json) || !cJSON_IsNumber(color_json))
    {
        return 0; // Condition not met
    }

    return 1; // Condition met
}

// Function to assign values to user structure fields from JSON data
static void assign_user_values(t_user *user, const cJSON *id_json, const cJSON *name_json, const cJSON *pass_json, const cJSON *color_json)
{
    // Assigning values to the user structure fields from JSON data
    user->user_id = id_json->valueint;
    user->name = mx_strdup(name_json->valuestring);
    user->password = mx_strdup(pass_json->valuestring);
    user->avatar_color = color_json->valueint;
    user->avatar_path = NULL; // Assuming avatar_path is not provided in JSON, setting it to NULL
}

// Function to set current user details from a JSON object
void set_current_user(t_user **user, const cJSON *user_json)
{
    if (!user_json)
    {
        exit(EXIT_FAILURE);
    }

    const cJSON *id_json, *name_json, *pass_json, *color_json;
    // Extract user information from the JSON object
    extract_user_info(user_json, &id_json, &name_json, &pass_json, &color_json);

    // Checking if any required field is missing or has invalid data
    if (!check_user_json(id_json, name_json, pass_json, color_json))
    {
        // If any required field is missing or has invalid data, return without setting user
        return;
    }

    // Allocating memory for the user structure
    *user = malloc(sizeof(t_user));

    if (!*user)
    {
        exit(EXIT_FAILURE);
    }

    // Assigning values to the user structure fields from JSON data
    assign_user_values(*user, id_json, name_json, pass_json, color_json);
}
