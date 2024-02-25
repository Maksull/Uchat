#include "../inc/server.h"

int db_delete_messages(int chat_id)
{
    char query[QUERY_LEN];
    sprintf(query, "DELETE FROM `messages` WHERE `chat_id` = '%d'", chat_id);
    if (db_execute_query(query) != 0)
    {
        return 1;
    }

    return 0;
}
