#include "../../inc/server.h"

// Get JSON formatted user information
static char *get_json_formatted_user(const t_user *user)
{
    // Create a cJSON object to hold user information
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", REQ_USR_LOGIN);              // Add request type
    cJSON_AddNumberToObject(json, "id", user->user_id);                // Add user ID
    cJSON_AddStringToObject(json, "username", user->name);             // Add username
    cJSON_AddStringToObject(json, "password", user->password);         // Add password
    cJSON_AddNumberToObject(json, "avatar_color", user->avatar_color); // Add avatar color
    cJSON_AddNumberToObject(json, "error_code", R_SUCCESS);            // Add success error code
    char *user_info = cJSON_PrintUnformatted(json);                    // Convert cJSON object to string
    cJSON_Delete(json);                                                // Delete cJSON object
    
    return user_info;                                                  // Return JSON formatted user information
}

// Set user account data from SQLite statement
static void set_user_account_data(sqlite3_stmt *stmt, t_server_utils *utils)
{
    // Check if the statement returned a row
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        // If a row is returned, create a user object and set its properties
        utils->user = mx_create_user(sqlite3_column_int64(stmt, 0), utils->client_socket, utils->ssl); // Create user object
        utils->user->name = mx_strdup((const char *)sqlite3_column_text(stmt, 1));                     // Set username
        utils->user->password = mx_strdup((const char *)sqlite3_column_text(stmt, 2));                 // Set password
        utils->user->avatar_color = sqlite3_column_int64(stmt, 3);                                     // Set avatar color
    }
    sqlite3_finalize(stmt); // Finalize the statement
}

// Set user account data by username and password
static t_response_code set_user_by_username(const char *username, const char *password, t_server_utils *utils)
{
    sqlite3 *db = open_db(); // Open the database connection
    sqlite3_stmt *stmt;            // SQLite statement

    // Prepare SQL statement to select user by username
    sqlite3_prepare_v2(db, "SELECT users.id, users.username, users.password, users.avatar_color "
                           "FROM `users` WHERE `username` = ?",
                       -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, username, -1, NULL); // Bind username parameter

    // Set user account data from the SQL statement
    set_user_account_data(stmt, utils);

    sqlite3_close(db); // Close the database connection

    // Check if user was found
    if (utils->user == NULL)
    {
        // If user was not found, return user not found error code
        return R_USR_NOENT;
    }

    // Check if password matches
    if (strcmp(utils->user->password, password) != 0)
    {
        // If password does not match, clear user object and return invalid password error code
        mx_clear_user(&utils->user);
        return R_INVALID_PASS;
    }

    char *response = get_json_formatted_user(utils->user); // Format JSON response
    send_response_to(utils->ssl, response);                // Send response to client
    free(response);                                        // Free allocated memory for response

    // Log user information
    char result_to_log[QUERY_LEN]; // Buffer to hold log message
    sprintf(result_to_log, "Logged in user info: id: %d, name: %s, color: %d",
            utils->user->user_id,
            utils->user->name,
            utils->user->avatar_color); // Format log message
    logger(result_to_log, INFO_LOG);    // Log user information

    return R_SUCCESS;
}

void handle_user_login(const cJSON *user_info, t_server_utils *utils)
{
    // Initialize the database
    if (init_db() != 0)
    {
        // If database initialization fails, send database failure response and return
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_USR_LOGIN); // Send database failure response
        return;                                                        // Return from function
    }

    int error_code = 0;
    const cJSON *user_name = cJSON_GetObjectItemCaseSensitive(user_info, "name");         // Get username from JSON
    const cJSON *user_password = cJSON_GetObjectItemCaseSensitive(user_info, "password"); // Get password from JSON

    // Check if username and password are strings
    if (!cJSON_IsString(user_name) || !cJSON_IsString(user_password))
    {
        // If username or password is not a string, send JSON failure response and return
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_USR_LOGIN); // Send JSON failure response
        return;
    }

    // Set user by username and password
    if ((error_code = set_user_by_username(user_name->valuestring, user_password->valuestring, utils)) != R_SUCCESS)
    {
        // If setting user by username and password fails, send corresponding error response
        send_server_response(utils->ssl, error_code, REQ_USR_LOGIN); // Send error response
    }
}
