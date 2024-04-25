#include "../../inc/client.h"

// Function to handle signup response
t_response_code handle_signup_res(const char *response_str)
{
    // Parse the JSON response
    cJSON *json = cJSON_Parse(response_str);
    const int error_code = get_res_code(json);

    // Delete the cJSON object
    cJSON_Delete(json);

    return error_code;
}
