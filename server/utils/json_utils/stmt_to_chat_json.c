#include "../../inc/server.h"

cJSON *stmt_to_chat_json(sqlite3_stmt *stmt, bool is_for_search)
{
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "chat_id", sqlite3_column_int64(stmt, 0));
    cJSON_AddStringToObject(json, "chat_name", (const char *)sqlite3_column_text(stmt, 1));
    cJSON_AddNumberToObject(json, "chat_color", sqlite3_column_int64(stmt, 2));
    cJSON_AddNumberToObject(json, "chat_permissions", !is_for_search ? sqlite3_column_int64(stmt, 3) : 1);

    return json;
}
