#include "../../inc/server.h"

// Function to validate JSON object for message deletion
static int validate_message_json(const cJSON *msg_json)
{
    const cJSON *message_id = cJSON_GetObjectItem(msg_json, "id");
    const cJSON *chat_id = cJSON_GetObjectItem(msg_json, "chat_id");

    if (!cJSON_IsNumber(message_id) || !cJSON_IsNumber(chat_id))
    {
        return 0; // JSON validation failed
    }

    return 1; // JSON validation succeeded
}

// Function to check if the chat exists
static int check_chat_exists(int chat_id)
{
    if (!db_chat_exists(chat_id))
    {
        return 0; // Chat doesn't exist
    }

    return 1; // Chat exists
}

// Function to check if the user is a member of the chat
static int check_user_chat_membership(int user_id, int chat_id)
{
    if (!db_is_chat_member(user_id, chat_id))
    {
        return 0; // User is not a member of the chat
    }

    return 1; // User is a member of the chat
}

// Function to delete a message from the database
static t_response_code delete_message_from_db(int message_id, int chat_id)
{
    char query[QUERY_LEN];
    sprintf(query, "DELETE FROM `messages` WHERE `id` = '%d' AND `chat_id` = '%d'", message_id, chat_id);

    if (db_execute_query(query) != 0)
    {
        return R_DB_FAILURE; // Database operation failed
    }

    return R_SUCCESS; // Message deletion successful
}

// Main function to delete a message
t_response_code db_delete_message(const cJSON *msg_json, t_server_utils *utils)
{
    if (!validate_message_json(msg_json))
    {
        return R_JSON_FAILURE; // JSON validation failed
    }

    int message_id = cJSON_GetObjectItem(msg_json, "id")->valueint;
    int chat_id = cJSON_GetObjectItem(msg_json, "chat_id")->valueint;

    if (!check_chat_exists(chat_id))
    {
        return R_CHAT_NOENT; // Chat doesn't exist
    }

    if (!check_user_chat_membership(utils->user->user_id, chat_id))
    {
        return R_ISNT_CHAT_MEMBER; // User is not a member of the chat
    }

    return delete_message_from_db(message_id, chat_id); // Delete the message from the database
}
