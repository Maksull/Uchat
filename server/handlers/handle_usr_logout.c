#include "../inc/server.h"

// Function handles the user logout request
t_request_type handle_usr_logout(const cJSON* logout_info, t_server_utils* utils) {
    const cJSON *client_exit = cJSON_GetObjectItemCaseSensitive(logout_info, "client_exit");

    // Check if the "client_exit" field exists and is of type number
    if (!cJSON_IsNumber(client_exit)) {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_USR_LOGOUT);
        return REQ_USR_LOGOUT;
    }

    // Extract the value of the "client_exit" field
    int is_client_exit = client_exit->valueint;

    // If a user is logged in, log the logout event
    if (utils->user) {
        char str[100];
        sprintf(str, "User (%d, %s) logging out\n", utils->user->user_id, utils->user->name);
        logger(str, INFO_LOG);
    }

    // Perform client cleanup
    client_cleanup(utils, is_client_exit);

    // Return the type of request based on whether the client is exiting or just logging out
    return is_client_exit ? REQ_CLIENT_EXIT : REQ_USR_LOGOUT;
}