#include "../../inc/client.h"

// Function to handle signup request
t_response_code handle_signup_req(const char *user_name, const char *user_password)
{
    // Suspend operations
    utils->is_suspended = true;

    // Create JSON object for signup request
    cJSON *json = create_signup_json(user_name, user_password);
    char *json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    // Send request to server and receive response
    char *response = send_and_receive_from_server(utils->ssl, json_str);

    // Handle signup response
    t_response_code error_code = handle_signup_res(response);

    // Log response
    logger(get_res_str(error_code), error_code == R_SUCCESS ? INFO_LOG : ERROR_LOG);

    // Free memory
    free(json_str);
    free(response);

    // Resume operations
    return error_code;
}
