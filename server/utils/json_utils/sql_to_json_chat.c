#include "../../inc/server.h"

// Convert SQLite statement to JSON
cJSON *sql_to_json_chat(sqlite3_stmt *stmt, bool is_for_search)
{
    // Create a JSON object
    cJSON *json = cJSON_CreateObject();

    // Add chat information to the JSON object
    cJSON_AddNumberToObject(json, "chat_id", sqlite3_column_int64(stmt, 0));
    cJSON_AddStringToObject(json, "chat_name", (const char *)sqlite3_column_text(stmt, 1));
    cJSON_AddNumberToObject(json, "chat_color", sqlite3_column_int64(stmt, 2));

    // Add chat permissions if it's not for search
    if (!is_for_search)
    {
        cJSON_AddNumberToObject(json, "chat_permissions", sqlite3_column_int64(stmt, 3));
    }
    else
    {
        cJSON_AddNumberToObject(json, "chat_permissions", 1); // For search, assume user has permissions
    }

    return json;
}
