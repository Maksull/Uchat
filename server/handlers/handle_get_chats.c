#include "../inc/server.h"

void handle_get_chats(const cJSON *chat_info, t_server_utils *utils)
{
    (void)chat_info;

    if (init_database() != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_GET_CHATS);
        return;
    }

    cJSON *json = cJSON_CreateObject();
    cJSON *chats = db_get_chats_by_user_id(utils->user->user_id);
    cJSON_AddItemReferenceToObject(json, "chats", chats);
    cJSON_AddNumberToObject(json, "type", REQ_GET_CHATS);
    cJSON_AddNumberToObject(json, "error_code", R_SUCCESS);

    char *json_str = cJSON_PrintUnformatted(json);
    send_response_to(utils->ssl, json_str);

    cJSON_Delete(chats);
    cJSON_Delete(json);
    free(json_str);
}
