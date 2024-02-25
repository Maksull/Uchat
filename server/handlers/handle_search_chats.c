#include "../inc/server.h"

void handle_search_chats(const cJSON *chat_info, t_server_utils *utils)
{
    if (init_database() != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_GET_CHATS);
        return;
    }

    cJSON *json = cJSON_CreateObject();
    cJSON *chats = db_get_search_chats(chat_info, utils);
    cJSON_AddItemReferenceToObject(json, "chats", chats);
    cJSON_AddNumberToObject(json, "type", REQ_SEARCH_CHATS);
    cJSON_AddNumberToObject(json, "error_code", R_SUCCESS);

    char *json_str = cJSON_PrintUnformatted(json);
    send_response_to(utils->ssl, json_str);

    cJSON_Delete(json);
    free(json_str);
}
