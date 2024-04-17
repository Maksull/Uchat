#include "../../inc/client.h"

// Function to create a JSON object for edit password request
static cJSON *create_edit_password_json(const char *new_pass, const char *old_pass)
{
    // Create JSON object for the request
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "new_password", new_pass);
    cJSON_AddStringToObject(json, "old_password", old_pass);
    cJSON_AddNumberToObject(json, "type", REQ_EDIT_PASSWORD);

    return json;
}

// Function to handle edit password request
t_response_code handle_edit_password_req(const char *new_pass, const char *old_pass)
{
    // Set the client as suspended
    utils->is_suspended = true;

    // Create JSON object for the request
    cJSON *json = create_edit_password_json(new_pass, old_pass);
    char *json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    // Send request to server and receive response
    char *response = send_and_receive_from_server(utils->ssl, json_str);
    // Handle the server response
    t_response_code error_code = handle_server_res(response);
    // Log the response
    logger(get_res_str(error_code), error_code == R_SUCCESS ? INFO_LOG : ERROR_LOG);

    // If response is successful, modify global user password
    (error_code == R_SUCCESS) ? modify_global_user(NULL, new_pass) : (void)0;

    // Free memory
    free(json_str);
    free(response);
    // Set the client as not suspended
    utils->is_suspended = false;

    return error_code;
}
