#include "../../inc/server.h"

// Function to handle the retrieval of the ID of the last message in a chat
void handle_last_msg_id(const cJSON *chat_info, t_server_utils *utils)
{
    // Initialize the database and check for initialization errors
    if (init_database() != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_LAST_MSG_ID);
        return;
    }

    int last_msg_id = -1;
    int error_code = 0;

    // Retrieve the last message ID and check for errors
    if ((error_code = db_get_last_message_id(chat_info, &last_msg_id)) != R_SUCCESS)
    {
        send_server_response(utils->ssl, error_code, REQ_LAST_MSG_ID);
        return;
    }

    cJSON *json = cJSON_CreateObject();
    // Add the last message ID, type and error_code fields to the response JSON object
    cJSON_AddNumberToObject(json, "last_msg_id", last_msg_id);
    cJSON_AddNumberToObject(json, "type", REQ_LAST_MSG_ID);
    cJSON_AddNumberToObject(json, "error_code", R_SUCCESS);

    char *json_str = cJSON_PrintUnformatted(json);
    send_response_to(utils->ssl, json_str);
    cJSON_Delete(json);
    free(json_str);
}
