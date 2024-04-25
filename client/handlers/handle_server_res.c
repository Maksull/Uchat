#include "../inc/client.h"

// Function to handle server response
t_response_code handle_server_res(const char *response_str)
{
    // Check if the response string is NULL
    if (response_str == NULL)
    {
        return R_INVALID_INPUT; // Return invalid input error code
    }

    cJSON *json = cJSON_Parse(response_str); // Parse the response string into a cJSON object
    int error_code = get_res_code(json); // Extract the error code from the cJSON object

    cJSON_Delete(json); // Delete the cJSON object to free memory

    return error_code; // Return the extracted error code
}
