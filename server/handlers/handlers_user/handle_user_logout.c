#include "../../inc/server.h"

// Function to get the value of the "client_exit" field from JSON
static int get_client_exit_flag(const cJSON *logout_info)
{
    const cJSON *client_exit = cJSON_GetObjectItemCaseSensitive(logout_info, "client_exit");
    if (!cJSON_IsNumber(client_exit))
    {
        return -1;
    }
    return client_exit->valueint;
}

// Function to log the logout event
static void log_logout_event(t_server_utils *utils)
{
    if (utils->user)
    {
        char str[100];
        sprintf(str, "User (%d, %s) logging out\n", utils->user->user_id, utils->user->name);
        logger(str, INFO_LOG);
    }
}

// Function to perform client cleanup and return the type of request
static t_request_type perform_client_cleanup(t_server_utils *utils, int is_client_exit)
{
    client_cleanup(utils, is_client_exit);
    return is_client_exit ? REQ_CLIENT_EXIT : REQ_USR_LOGOUT;
}

// Function to handle user logout request
t_request_type handle_user_logout(const cJSON *logout_info, t_server_utils *utils)
{
    int is_client_exit = get_client_exit_flag(logout_info);
    if (is_client_exit < 0)
    {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_USR_LOGOUT);
        return REQ_USR_LOGOUT;
    }

    log_logout_event(utils);
    return perform_client_cleanup(utils, is_client_exit);
}
