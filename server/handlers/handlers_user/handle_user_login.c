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

    return user_info; // Return JSON formatted user information
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

// Function to prepare SQL statement to select user by username
static sqlite3_stmt *prepare_select_user_statement(sqlite3 *db, const char *username)
{
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, "SELECT users.id, users.username, users.password, users.avatar_color "
                                    "FROM `users` WHERE `username` = ?",
                                -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        char error[100];
        sprintf(error, "Cannot prepare statement: %s\n", sqlite3_errmsg(db));
        logger(error, ERROR_LOG);
        return NULL;
    }

    sqlite3_bind_text(stmt, 1, username, -1, NULL);
    return stmt;
}

// Function to validate user password
static t_response_code validate_user_password(t_server_utils *utils, const char *password)
{
    if (strcmp(utils->user->password, password) != 0)
    {
        mx_clear_user(&utils->user);
        return R_INVALID_PASS;
    }
    return R_SUCCESS;
}

// Function to send user information response to the client
static void send_user_info_response(t_server_utils *utils)
{
    char *response = get_json_formatted_user(utils->user);
    send_response_to(utils->ssl, response);
    free(response);
}

// Function to log user information
static void log_user_information(t_server_utils *utils)
{
    char result_to_log[QUERY_LEN];
    sprintf(result_to_log, "Logged in user info: id: %d, name: %s, color: %d",
            utils->user->user_id,
            utils->user->name,
            utils->user->avatar_color);
    logger(result_to_log, INFO_LOG);
}

// Set user account data by username and password
static t_response_code set_user_by_username(const char *username, const char *password, t_server_utils *utils)
{
    sqlite3 *db = open_db(); // Open the database connection
    if (!db)
    {
        return R_DB_FAILURE;
    }

    sqlite3_stmt *stmt = prepare_select_user_statement(db, username);
    if (!stmt)
    {
        sqlite3_close(db);
        return R_DB_FAILURE;
    }

    set_user_account_data(stmt, utils);
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    if (!utils->user)
    {
        return R_USR_NOENT;
    }

    t_response_code password_validation_result = validate_user_password(utils, password);
    if (password_validation_result != R_SUCCESS)
    {
        mx_clear_user(&utils->user);
        return password_validation_result;
    }

    send_user_info_response(utils);
    log_user_information(utils);

    return R_SUCCESS;
}

// Function to initialize the database
static int initialize_database(t_server_utils *utils)
{
    if (init_db() != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_USR_LOGIN);
        return R_DB_FAILURE;
    }
    return R_SUCCESS;
}


void handle_user_login(const cJSON *user_info, t_server_utils *utils)
{
    // Initialize the database
    if (initialize_database(utils) != R_SUCCESS)
    {
        return;
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
