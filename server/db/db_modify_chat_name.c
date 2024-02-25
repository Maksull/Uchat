#include "../inc/server.h"

t_response_code db_modify_chat_name(int chat_id, const char *new_name)
{

    int chat_id_for_check = db_get_chat_id_by_name(new_name);
    if (chat_id_for_check != -1)
    {
        return R_CHAT_EXISTS;
    }

    char query[QUERY_LEN];
    sprintf(query, "UPDATE `chats` SET `name` = '%s' WHERE `id` = '%d'", new_name, chat_id);

    if (db_execute_query(query) != 0)
    {
        return R_DB_FAILURE;
    }
    
    return R_SUCCESS;
}