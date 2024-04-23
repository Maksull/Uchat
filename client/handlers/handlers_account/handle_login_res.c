#include "../../inc/client.h"

// Function to handle login response
t_response_code handle_login_res(const char *response_str)
{
    // Check for invalid input
    if (response_str == NULL)
    {
        return R_INVALID_INPUT;
    }

    // Parse response JSON
    cJSON *json = cJSON_Parse(response_str);
    int error_code = get_res_code(json);

    // If response indicates an error, return the error code
    if (error_code != R_SUCCESS)
    {
        cJSON_Delete(json);
        
        return error_code;
    }

    // Set current user based on response JSON
    pthread_mutex_lock(&utils->lock);
    set_current_user(&utils->current_user, json);
    pthread_mutex_unlock(&utils->lock);

    // Cleanup JSON
    cJSON_Delete(json);

    // Check if setting current user failed
    if (utils->current_user == NULL)
    {
        return R_JSON_FAILURE;
    }

    return R_SUCCESS;
}
