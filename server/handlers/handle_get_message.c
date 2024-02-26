#include "../inc/server.h"

// Function to retrieve a message by its ID from the database
static cJSON *get_msg_by_id(const cJSON *msg_info)
{
    // Extract chat_id and message_id from the JSON object
    const cJSON *chat_id = cJSON_GetObjectItemCaseSensitive(msg_info, "chat_id");
    const cJSON *message_id = cJSON_GetObjectItemCaseSensitive(msg_info, "message_id");

    // Check if chat_id and message_id are numbers
    if (!cJSON_IsNumber(chat_id) || !cJSON_IsNumber(message_id))
    {
        return NULL;
    }

    sqlite3 *db = open_database();
    sqlite3_stmt *stmt;

    // Prepare the SQL statement to retrieve the message from the database
    sqlite3_prepare_v2(db, "SELECT messages.id, messages.user_id, users.username, users.avatar_color, messages.chat_id, messages.text, messages.date "
                           "FROM `messages` INNER JOIN `users` ON users.id = messages.user_id "
                           "WHERE messages.chat_id = ? AND messages.id = ?",
                       -1, &stmt, NULL);

    // Bind the values for chat_id and message_id to the SQL statement
    sqlite3_bind_int64(stmt, 1, chat_id->valueint);
    sqlite3_bind_int64(stmt, 2, message_id->valueint);

    cJSON *message_json = NULL;
    // If the SQL query returns a row, extract the message JSON
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        message_json = get_msg_json(stmt);
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return message_json;
}

// Function to handle the retrieval of a message
void handle_get_msg(const cJSON *msg_info, t_server_utils *utils)
{
    // Initialize the database and check for initialization errors
    if (database_init() != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_GET_CHATS);
        return;
    }

    cJSON *msg_json = get_msg_by_id(msg_info);

    // If the message JSON is NULL, send a server response with JSON failure code
    if (msg_json == NULL)
    {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_GET_MSG);
        return;
    }

    cJSON *json = cJSON_CreateObject();

    // Add message,type and error_code to response JSON object
    cJSON_AddItemReferenceToObject(json, "message", msg_json);
    cJSON_AddNumberToObject(json, "type", REQ_GET_MSG);
    cJSON_AddNumberToObject(json, "error_code", R_SUCCESS);

    char *json_str = cJSON_PrintUnformatted(json);
    send_response_to(utils->ssl, json_str);
    cJSON_Delete(json);
    free(json_str);
}
