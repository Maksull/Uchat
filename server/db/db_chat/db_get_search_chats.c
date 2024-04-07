#include "../../inc/server.h"

// Get search results for chats from the database based on a search pattern
cJSON *db_get_search_chats(const cJSON *chat_info, t_server_utils *utils)
{
    cJSON *search_pattern = cJSON_GetObjectItemCaseSensitive(chat_info, "search_pattern"); // Get search pattern from JSON object

    // Check if the search pattern is a string
    if (!cJSON_IsString(search_pattern))
    {
        return NULL;
    }

    cJSON *chats_json = cJSON_CreateArray(); // Create a JSON array for search results

    sqlite3 *db = open_db(); // Open the database connection

    // Prepare SQL statement to search for chats based on the provided search pattern
    sqlite3_stmt *stmt;                                                       // SQLite statement object
    char *search_str = mx_strnew(mx_strlen(search_pattern->valuestring) + 4); // Allocate memory for search pattern
    mx_strcat(search_str, "%%");                                              // Add wildcard prefix
    mx_strcat(search_str, search_pattern->valuestring);                       // Append search pattern
    mx_strcat(search_str, "%%");                                              // Add wildcard suffix
    sqlite3_prepare_v2(db, "SELECT chats.id, chats.name, chats.avatar_color FROM chats "
                           "WHERE chats.name LIKE ? "
                           "AND chats.id NOT IN (SELECT `chat_id` FROM `members` WHERE `user_id` = ?) "
                           "ORDER BY chats.date DESC ",
                       -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, search_str, -1, NULL);
    sqlite3_bind_int64(stmt, 2, utils->user->user_id);

    // Iterate over the search results and add each chat to the JSON array
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        cJSON_AddItemToArray(chats_json, sql_to_json_chat(stmt, true)); // Convert current row to JSON and add to array
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    mx_strdel(&search_str); // Free memory allocated for search pattern

    return chats_json; // Return the JSON array containing the search results
}
