#include "../inc/server.h"

t_response_code db_delete_chat(const char *chat_name, int chat_id)
{

    if (!db_chat_exists(chat_id))
    {
        return R_CHAT_NOENT;
    }

    char query[QUERY_LEN];
    sprintf(query, "DELETE FROM `chats` WHERE `name` = '%s'", chat_name);

    if (db_execute_query(query) != 0)
    {
        return R_DB_FAILURE;
    }
    
    return 0;
}
