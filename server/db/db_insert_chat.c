#include "../inc/server.h"

t_response_code db_insert_chat(const char *chat_name, int date, int avatar_color)
{
    int chat_id = db_get_chat_id_by_name(chat_name);
    
    if (chat_id != -1)
    {
        return R_CHAT_EXISTS;
    }

    char query[QUERY_LEN];
    sprintf(query, "INSERT INTO `chats` (`name`, `date`, `avatar_color`) VALUES('%s', '%d', '%d')",
            chat_name, date, avatar_color);

    if (db_execute_query(query) != 0)
    {
        return R_DB_FAILURE;
    }

    return 0;
}
