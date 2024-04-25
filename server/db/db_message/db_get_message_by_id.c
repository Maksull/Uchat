#include "../../inc/server.h"

// Function to prepare a database SQL statement to retrieve a message by its ID and chat ID
static sqlite3_stmt *prepare_db_statement_for_message(sqlite3 *db, int chat_id, int message_id) {
    sqlite3_stmt *sql_stmt;
    // SQL query to select message details from the database
    const char *sql_query = "SELECT messages.id, messages.user_id, users.username, users.avatar_color, messages.chat_id, messages.text, messages.date "
                            "FROM `messages` INNER JOIN `users` ON users.id = messages.user_id "
                            "WHERE messages.chat_id = ? AND messages.id = ?";
    
    // Prepare the SQL statement
    sqlite3_prepare_v2(db, sql_query, -1, &sql_stmt, NULL);
    // Bind chat_id and message_id to the SQL statement parameters
    sqlite3_bind_int64(sql_stmt, 1, chat_id);
    sqlite3_bind_int64(sql_stmt, 2, message_id);

    return sql_stmt; // Return the prepared SQL statement
}

// Function to convert a database result to a cJSON JSON object
static cJSON *convert_db_result_to_json(sqlite3_stmt *sql_stmt) {
    cJSON *message_json = NULL;

    // If the SQL query returns a row, extract message details and create a JSON object
    if (sqlite3_step(sql_stmt) == SQLITE_ROW) {
        message_json = sql_to_json_message(sql_stmt); // Assuming sql_to_json_message() function exists
    }

    return message_json; // Return the cJSON JSON object
}

// Function to retrieve a message by its ID from the database
cJSON *db_get_message_by_id(const cJSON *msg_info)
{
    // Extract chat_id and message_id from the JSON object
    const cJSON *chat_id = cJSON_GetObjectItemCaseSensitive(msg_info, "chat_id");
    const cJSON *message_id = cJSON_GetObjectItemCaseSensitive(msg_info, "message_id");

    // Check if chat_id and message_id are numbers
    if (!cJSON_IsNumber(chat_id) || !cJSON_IsNumber(message_id))
    {
        return NULL; // Return NULL if chat_id or message_id is not a number
    }

    // Open the database connection
    sqlite3 *db = open_db();
    // Prepare the SQL statement to retrieve the message from the database
    sqlite3_stmt *sql_stmt = prepare_db_statement_for_message(db, chat_id->valueint, message_id->valueint);
    // Convert the database result to a cJSON JSON object
    cJSON *message_json = convert_db_result_to_json(sql_stmt);

    // Finalize the SQL statement and close the database connection
    sqlite3_finalize(sql_stmt);
    sqlite3_close(db);

    return message_json; // Return the cJSON JSON object
}
