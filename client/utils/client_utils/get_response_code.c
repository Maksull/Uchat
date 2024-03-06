#include "../../inc/client.h"

// Get the response code from a JSON object
t_response_code get_response_code(cJSON *json)
{
    // Check if JSON object is valid
    if (json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            char error[200];
            sprintf(error, "Error before: %s\n", error_ptr);
            logger(error, ERROR_LOG);
        }
        return R_JSON_FAILURE;
    }

    // Extract and return the response code from the JSON object
    return cJSON_GetObjectItemCaseSensitive(json, "error_code")->valueint;
}
