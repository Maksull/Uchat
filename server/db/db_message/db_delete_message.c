#include "../../inc/server.h"

// Function to delete a message from the database
t_response_code db_delete_message(const cJSON *msg_json, t_server_utils *utils)
{
    // Extract message_id and chat_id from the JSON object
    const cJSON *message_id = cJSON_GetObjectItem(msg_json, "id");
    const cJSON *chat_id = cJSON_GetObjectItem(msg_json, "chat_id");

    // Validate that both message_id and chat_id are numbers
    if (!cJSON_IsNumber(message_id) || !cJSON_IsNumber(chat_id))
    {
        return R_JSON_FAILURE;
    }

    // Check if the chat identified by chat_id exists
    if (!db_chat_exists(chat_id->valueint))
    {
        return R_CHAT_NOENT;
    }

    // Check if the user identified by utils->user->user_id is a member of the chat
    if (!db_is_chat_member(utils->user->user_id, chat_id->valueint))
    {
        return R_ISNT_CHAT_MEMBER;
    }

    // Construct SQL query to delete the message from the messages table
    char query[QUERY_LEN];
    sprintf(query, "DELETE FROM `messages` WHERE `id` = '%d' AND `chat_id` = '%d'",
            message_id->valueint, chat_id->valueint);

    // Execute the SQL query and check for errors
    if (db_execute_query(query) != 0)
    {
        return R_DB_FAILURE;
    }

    return R_SUCCESS;
}
