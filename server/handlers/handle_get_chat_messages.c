#include "../inc/server.h"

// Get a single message in JSON format
cJSON *get_msg_json(sqlite3_stmt *stmt)
{

    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "msg_id", sqlite3_column_int64(stmt, 0));
    cJSON_AddNumberToObject(json, "sender_id", sqlite3_column_int64(stmt, 1));
    cJSON_AddStringToObject(json, "sender_name", (const char *)sqlite3_column_text(stmt, 2));
    cJSON_AddNumberToObject(json, "sender_color", sqlite3_column_int(stmt, 3));
    cJSON_AddNumberToObject(json, "chat_id", sqlite3_column_int64(stmt, 4));
    cJSON_AddStringToObject(json, "text", (const char *)sqlite3_column_text(stmt, 5));
    cJSON_AddNumberToObject(json, "date", sqlite3_column_int64(stmt, 6));
    return json;
}

// Get messages array in JSON format
static cJSON *get_msgs_array_json(int chat_id)
{

    cJSON *chats_json = cJSON_CreateArray();
    sqlite3 *db = open_database();
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, "SELECT messages.id, messages.user_id, users.username, users.avatar_color, messages.chat_id, messages.text, messages.date "
                           "FROM `messages` INNER JOIN `users` ON users.id = messages.user_id "
                           "WHERE messages.chat_id = ?",
                       -1, &stmt, NULL);

    sqlite3_bind_int64(stmt, 1, chat_id);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {

        cJSON_AddItemToArray(chats_json, get_msg_json(stmt));
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return chats_json;
}

// Function to handle the retrieval of messages for a chat
void handle_get_chat_msgs(const cJSON *chat_info, t_server_utils *utils)
{
    // Initialize the database and check for initialization errors
    if (database_init() != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_GET_CHAT_MSGS);
        return;
    }

    const cJSON *chat_id = cJSON_GetObjectItemCaseSensitive(chat_info, "chat_id");

    // Check if chat_id is a number
    if (!cJSON_IsNumber(chat_id))
    {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_GET_CHAT_MSGS);
        return;
    }

    // Check if the chat exists in the database
    if (!db_chat_exists(chat_id->valueint))
    {
        send_server_response(utils->ssl, R_CHAT_NOENT, REQ_GET_CHAT_MSGS);
        return;
    }

    // Check if the user is a member of the chat
    if (!db_is_chat_member(utils->user->user_id, chat_id->valueint))
    {
        send_server_response(utils->ssl, R_ISNT_CHAT_MEMBER, REQ_GET_CHAT_MSGS);
        return;
    }

    cJSON *json = cJSON_CreateObject();
    cJSON *messages = get_msgs_array_json(chat_id->valueint);
    cJSON_AddItemReferenceToObject(json, "messages", messages);

    // Add type, error_code fields to the JSON object
    cJSON_AddNumberToObject(json, "type", REQ_GET_CHAT_MSGS);
    cJSON_AddNumberToObject(json, "error_code", R_SUCCESS);

    char *json_str = cJSON_PrintUnformatted(json);
    send_response_to(utils->ssl, json_str);
    cJSON_Delete(messages);
    cJSON_Delete(json);
    free(json_str);
}
