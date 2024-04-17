#include "../../inc/client.h"

// Function to create a JSON object for delete account request
static cJSON *create_delete_account_json()
{
    // Create JSON object for the request
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", REQ_DELETE_ACCOUNT);

    return json;
}

// Function to handle deleting an account request
t_response_code handle_delete_account_req()
{
    // Set the client as suspended
    utils->is_suspended = true;

    // Create JSON object for the request
    cJSON *json = create_delete_account_json();
    char *json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    // Send request to server and receive response
    char *response = send_and_receive_from_server(utils->ssl, json_str);

    // Handle the server response
    int error_code = handle_server_res(response);
    // Log the response
    logger(get_res_str(error_code), error_code == R_SUCCESS ? INFO_LOG : ERROR_LOG);

    // Free memory
    free(json_str);
    free(response);

    return error_code;
}
