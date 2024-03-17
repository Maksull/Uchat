#include "../inc/client.h"

t_response_code handle_send_msg_request(const char *message_str)
{
    utils->is_suspended = true;

    unsigned long curr_time = get_current_time();
    t_msg *sent_msg = mx_create_msg(-1, utils->current_user->user_id, utils->current_user->name, utils->current_chat->id,
                                    message_str, get_string_time(curr_time), utils->current_user->avatar_color);

    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", REQ_SEND_MESSAGE);
    cJSON_AddStringToObject(json, "text", sent_msg->text);
    cJSON_AddNumberToObject(json, "user_id", sent_msg->sender_id);
    cJSON_AddStringToObject(json, "user_name", sent_msg->sender_name);
    cJSON_AddNumberToObject(json, "chat_id", sent_msg->chat_id);
    cJSON_AddNumberToObject(json, "date", curr_time);
    char *json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    char *response = send_and_recv_from_server(utils->ssl, json_str);
    int error_code = handle_send_msg_response(response, sent_msg);
    logger(get_response_str(error_code), error_code == R_SUCCESS ? INFO_LOG : ERROR_LOG);

    free(response);
    utils->is_suspended = false;

    return error_code;
}
