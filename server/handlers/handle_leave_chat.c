#include "../inc/server.h"

void handle_leave_chat(const cJSON *chat_info, t_server_utils *utils)
{
    if (init_database() != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_LEAVE_CHAT);
        return;
    }

    const cJSON *chat_name = cJSON_GetObjectItemCaseSensitive(chat_info, "name");

    if (!cJSON_IsString(chat_name))
    {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_LEAVE_CHAT);
        return;
    }

    int chat_id = db_get_chat_id_by_name(chat_name->valuestring);
    int error_code = 0;

    if ((error_code = db_delete_member(utils->user->user_id, chat_id)) != 0)
    {
        send_server_response(utils->ssl, error_code, REQ_LEAVE_CHAT);
        return;
    }
    send_server_response(utils->ssl, R_SUCCESS, REQ_LEAVE_CHAT);
}
