#include "../../inc/server.h"

// Function to search chats based on a search pattern in the database
static cJSON *search_chats_in_db(const char *search_pattern, int user_id, sqlite3 *db)
{
    // Create a JSON array to store information about the searched chats.
    cJSON *chats_json = cJSON_CreateArray();

    // Construct the search string to be used in the SQL query.
    char *search_str = mx_strnew(mx_strlen(search_pattern) + 4);
    mx_strcat(search_str, "%%");
    mx_strcat(search_str, search_pattern);
    mx_strcat(search_str, "%%");

    // Declare a SQLite3 statement object.
    sqlite3_stmt *sql_stmt;
    // Prepare the SQL statement to search for chats matching the search pattern.
    sqlite3_prepare_v2(db, "SELECT chats.id, chats.name, chats.avatar_color FROM chats "
                           "WHERE chats.name LIKE ? "
                           "AND chats.id NOT IN (SELECT `chat_id` FROM `members` WHERE `user_id` = ?) "
                           "ORDER BY chats.date DESC ",
                       -1, &sql_stmt, NULL);
    // Bind the search string and user ID parameters to the SQL statement.
    sqlite3_bind_text(sql_stmt, 1, search_str, -1, NULL);
    sqlite3_bind_int64(sql_stmt, 2, user_id);

    // Iterate over the result rows and add information about the searched chats to the JSON array.
    while (sqlite3_step(sql_stmt) == SQLITE_ROW)
    {
        cJSON_AddItemToArray(chats_json, sql_to_json_chat(sql_stmt, true));
    }

    // Finalize the SQL statement to release resources.
    sqlite3_finalize(sql_stmt);
    // Free the dynamically allocated memory for the search string.
    mx_strdel(&search_str);

    // Return the JSON array containing information about the searched chats.
    return chats_json;
}

// Original function refactored
cJSON *db_get_search_chats(const cJSON *chat_info, t_server_utils *utils)
{
    // Retrieve the search pattern from the provided JSON object.
    cJSON *search_pattern = cJSON_GetObjectItemCaseSensitive(chat_info, "search_pattern");

    // Validate that the search pattern is a string.
    if (!cJSON_IsString(search_pattern))
    {
        return NULL;
    }

    // Open the database connection.
    sqlite3 *db = open_db();
    // Search for chats in the database based on the search pattern.
    cJSON *chats_json = search_chats_in_db(search_pattern->valuestring, utils->user->user_id, db);
    // Close the database connection.
    sqlite3_close(db);

    // Return the JSON array containing information about the searched chats.
    return chats_json;
}
