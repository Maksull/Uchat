#include "../inc/server.h"

t_response_code db_delete_member(int user_id, int chat_id)
{

    if (!db_chat_exists(chat_id))
    {
        return R_CHAT_NOENT;
    }

    if (!db_is_chat_member(user_id, chat_id))
    {
        return R_ISNT_CHAT_MEMBER;
    }

    if (!db_has_chat_perms(user_id, chat_id, NORMAL_MEMBER))
    {
        return R_NO_CHAT_PERMS;
    }

    char query[QUERY_LEN];
    sprintf(query, "DELETE FROM `members` WHERE `user_id` = '%d' AND `chat_id` = '%d'", user_id, chat_id);
    if (db_execute_query(query) != 0)
    {
        return R_DB_FAILURE;
    }

    return R_SUCCESS;
}