#include "../../inc/server.h"

// Get the type of the request from the read json object
static t_request_type get_request_type(cJSON *json)
{
    return cJSON_GetObjectItem(json, "type")->valueint;
}

// Log cJSON parsing error
static void log_json_error()
{
    const char *error_ptr = cJSON_GetErrorPtr();
    if (error_ptr != NULL)
    {
        char error[200];
        sprintf(error, "Error before: %s\n", error_ptr);
        logger(error, ERROR_LOG);
    }
}

// Handle user logout request
static t_request_type handle_user_logout_request(cJSON *json, t_server_utils *utils)
{
    t_request_type type = handle_user_logout(json, utils);
    cJSON_Delete(json);
    
    return type;
}

// Handle other types of requests
static void handle_other_requests(t_request_type type, cJSON *json, t_server_utils *utils)
{
    request_handlers[type](json, utils);
    cJSON_Delete(json);
}

// Call a handler for any valid client request
t_request_type handle_request_for(const char *request, t_server_utils *utils)
{
    // Parse the request string into a cJSON object
    cJSON *json = cJSON_Parse(request);

    // Check if parsing was successful
    if (json == NULL)
    {
        log_json_error();

        return -1;
    }

    // Extract the request type from the JSON object
    t_request_type type = get_request_type(json);

    if (type == REQ_USR_LOGOUT)
    {
        // Call the handler function for user logout request
        return handle_user_logout_request(json, utils);
    }

    // Call the appropriate request handler function based on the request type
    handle_other_requests(type, json, utils);

    return type;
}
