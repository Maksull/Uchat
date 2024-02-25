#include "../inc/server.h"

void handle_edit_chat(const cJSON *chat_info, t_server_utils *utils)
{
    if (init_database() != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_EDIT_CHAT);
        return;
    }
    const cJSON *chat_id = cJSON_GetObjectItemCaseSensitive(chat_info, "chat_id");
    const cJSON *new_name = cJSON_GetObjectItemCaseSensitive(chat_info, "chat_name");

    if (!cJSON_IsString(new_name) || !cJSON_IsNumber(chat_id))
    {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_EDIT_CHAT);
        return;
    }

    if (!db_chat_exists(chat_id->valueint))
    {
        send_server_response(utils->ssl, R_CHAT_NOENT, REQ_EDIT_CHAT);
        return;
    }

    if (!is_strlen_valid(new_name->valuestring, MIN_NAME_INPUT_LEN, MAX_NAME_INPUT_LEN))
    {
        send_server_response(utils->ssl, R_NAME_LEN_INVALID, REQ_EDIT_CHAT);
        return;
    }

    if (!is_user_name_format_valid(new_name->valuestring))
    {
        send_server_response(utils->ssl, R_NAME_FORMAT_INVALID, REQ_EDIT_CHAT);
        return;
    }

    t_response_code resp_code = 0;
    if ((resp_code = db_modify_chat_name(chat_id->valueint, new_name->valuestring)) != R_SUCCESS)
    {
        send_server_response(utils->ssl, resp_code, REQ_EDIT_CHAT);
        return;
    }

    send_server_response(utils->ssl, R_SUCCESS, REQ_EDIT_CHAT);
}