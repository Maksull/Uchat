#include "../../inc/server.h"

// Delete a member from a chat in the database
t_response_code db_delete_member(int user_id, int chat_id)
{
    // Check if the chat exists
    if (!db_chat_exists(chat_id))
    {
        return R_CHAT_NOENT;
    }

    // Check if the user is a member of the chat
    if (!db_is_chat_member(user_id, chat_id))
    {
        return R_ISNT_CHAT_MEMBER;
    }

    // Check if the user has permissions to delete members from the chat
    if (!db_has_chat_perms(user_id, chat_id, NORMAL_MEMBER))
    {
        return R_NO_CHAT_PERMS;
    }

    // Create SQL query to delete the member from the chat
    char query[QUERY_LEN];
    sprintf(query, "DELETE FROM `members` WHERE `user_id` = '%d' AND `chat_id` = '%d'", user_id, chat_id);

    // Execute the SQL query
    if (db_execute_query(query) != 0)
    {
        return R_DB_FAILURE;
    }

    return R_SUCCESS;
}
