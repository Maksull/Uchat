#include "../../inc/server.h"

// Get a single message in JSON format
cJSON *sql_to_json_message(sqlite3_stmt *stmt)
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
