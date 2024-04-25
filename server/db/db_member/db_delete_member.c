#include "../../inc/server.h"

// Function to check if the chat exists
static int check_chat_existence(int chat_id)
{
    if (!db_chat_exists(chat_id))
    {
        return 0; // Return false if the chat does not exist
    }

    return 1; // Return true if the chat exists
}

// Function to check if the user is a member of the chat
static int check_user_membership(int user_id, int chat_id)
{
    if (!db_is_chat_member(user_id, chat_id))
    {
        return 0; // Return false if the user is not a member of the chat
    }

    return 1; // Return true if the user is a member of the chat
}

// Function to check if the user has permissions to delete members from the chat
static int check_user_permissions(int user_id, int chat_id)
{
    if (!db_has_chat_perms(user_id, chat_id, NORMAL_MEMBER))
    {
        return 0; // Return false if the user does not have permissions
    }

    return 1; // Return true if the user has permissions
}

// Delete a member from a chat in the database
t_response_code db_delete_member(int user_id, int chat_id)
{
    // Check if the chat exists
    if (!check_chat_existence(chat_id))
    {
        return R_CHAT_NOENT; // Return chat does not exist code
    }

    // Check if the user is a member of the chat
    if (!check_user_membership(user_id, chat_id))
    {
        return R_ISNT_CHAT_MEMBER; // Return not a member of the chat code
    }

    // Check if the user has permissions to delete members from the chat
    if (!check_user_permissions(user_id, chat_id))
    {
        return R_NO_CHAT_PERMS; // Return no permission code
    }

    // Create SQL query to delete the member from the chat
    char query[QUERY_LEN];
    snprintf(query, QUERY_LEN, "DELETE FROM `members` WHERE `user_id` = '%d' AND `chat_id` = '%d'", user_id, chat_id);

    // Execute the SQL query
    if (db_execute_query(query) != 0)
    {
        return R_DB_FAILURE; // Return database failure code
    }

    return R_SUCCESS; // Return success code
}
