#include "../../inc/server.h"

// Function to handle the retrieval of a message
void handle_get_msg(const cJSON *msg_info, t_server_utils *utils)
{
    // Initialize the database and check for initialization errors
    if (init_database() != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_GET_CHATS);
        return;
    }

    cJSON *msg_json = db_get_message_by_id(msg_info);

    // If the message JSON is NULL, send a server response with JSON failure code
    if (msg_json == NULL)
    {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_GET_MSG);
        return;
    }

    cJSON *json = cJSON_CreateObject();

    // Add message,type and error_code to response JSON object
    cJSON_AddItemReferenceToObject(json, "message", msg_json);
    cJSON_AddNumberToObject(json, "type", REQ_GET_MSG);
    cJSON_AddNumberToObject(json, "error_code", R_SUCCESS);

    char *json_str = cJSON_PrintUnformatted(json);
    send_response_to(utils->ssl, json_str);
    cJSON_Delete(json);
    free(json_str);
}
