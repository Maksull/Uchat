#include "../inc/server.h"

// Function to retrieve the ID of the last message in a chat from the database
t_response_code get_last_msg_id(const cJSON* chat_info, int* last_msg_id) {
    // Extract chat_id from the JSON object
    const cJSON *chat_id = cJSON_GetObjectItemCaseSensitive(chat_info, "chat_id");
    
    // Check if chat_id is a number
    if (!cJSON_IsNumber(chat_id)) {
        return R_JSON_FAILURE; 
    }

    // Check if the chat exists in the database
    if (!db_chat_exists(chat_id->valueint)) {
        return R_CHAT_NOENT; 
    }

    // Construct the SQL query to retrieve the ID of the last message in the chat
    char query[QUERY_LEN];
    sprintf(query, "SELECT id FROM `messages` WHERE chat_id = %d ORDER BY id DESC LIMIT 1", 
            chat_id->valueint);
    
    sqlite3* db = open_database();
    // Execute the SQL query and get the result
    sqlite3_stmt* stmt = db_execute_stmt_for(query, db);
    *last_msg_id = sqlite3_column_int64(stmt, 0);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    
    return R_SUCCESS; 
}

// Function to handle the retrieval of the ID of the last message in a chat
void handle_last_msg_id(const cJSON* chat_info, t_server_utils* utils) {
    // Initialize the database and check for initialization errors
    if (database_init() != 0) {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_LAST_MSG_ID);
        return;
    }

    int last_msg_id = -1;
    int error_code = 0;

    // Retrieve the last message ID and check for errors
    if ((error_code = get_last_msg_id(chat_info, &last_msg_id)) != R_SUCCESS) {
        send_server_response(utils->ssl, error_code, REQ_LAST_MSG_ID);
        return;
    }

    cJSON* json = cJSON_CreateObject();
    // Add the last message ID, type and error_code fields to the response JSON object
    cJSON_AddNumberToObject(json, "last_msg_id", last_msg_id);
    cJSON_AddNumberToObject(json, "type", REQ_LAST_MSG_ID);
    cJSON_AddNumberToObject(json, "error_code", R_SUCCESS);
    
    char* json_str = cJSON_PrintUnformatted(json);
    send_response_to(utils->ssl, json_str);
    cJSON_Delete(json);
    free(json_str);
}

