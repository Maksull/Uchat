#include "../../inc/server.h"

// Function to initialize the database and handle initialization errors
int initialize_database(t_server_utils *utils, t_request_type request_type)
{
    if (init_db() != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, request_type);

        return 1; // Error
    }
    
    return 0; // Success
}

// Function to extract chat ID and new name from the JSON object and validate them
int extract_and_validate_chat_info(const cJSON *chat_info, const cJSON **chat_id, const cJSON **new_name, t_server_utils *utils)
{
    *chat_id = cJSON_GetObjectItemCaseSensitive(chat_info, "chat_id");
    *new_name = cJSON_GetObjectItemCaseSensitive(chat_info, "chat_name");

    // Validate new name and chat ID
    if (!cJSON_IsString(*new_name) || !cJSON_IsNumber(*chat_id))
    {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_EDIT_CHAT); // Send response indicating JSON failure

        return 1;                                                        // Error
    }

    return 0; // Success
}

// Function to check if the chat exists
int check_chat_existence(const cJSON *chat_id, t_server_utils *utils)
{
    // Check if the chat exists
    if (!db_chat_exists(chat_id->valueint))
    {
        send_server_response(utils->ssl, R_CHAT_NOENT, REQ_EDIT_CHAT); // Send response indicating chat does not exist

        return 1;                                                      // Error
    }

    return 0; // Success
}

// Function to validate the new name length and format
int validate_new_name(const cJSON *new_name, t_server_utils *utils)
{
    // Validate the new name length
    if (!is_strlen_valid(new_name->valuestring, MIN_NAME_INPUT_LEN, MAX_NAME_INPUT_LEN))
    {
        send_server_response(utils->ssl, R_NAME_LEN_INVALID, REQ_EDIT_CHAT); // Send response indicating invalid name length

        return 1;                                                            // Error
    }

    // Validate the new name format
    if (!is_user_name_format_valid(new_name->valuestring))
    {
        send_server_response(utils->ssl, R_NAME_FORMAT_INVALID, REQ_EDIT_CHAT); // Send response indicating invalid name format

        return 1;                                                               // Error
    }

    return 0; // Success
}

// Function to modify the chat name
int modify_chat_name(const cJSON *chat_id, const cJSON *new_name, t_server_utils *utils)
{
    // Modify the chat name
    t_response_code resp_code = db_modify_chat_name(chat_id->valueint, new_name->valuestring);
    if (resp_code != R_SUCCESS)
    {
        send_server_response(utils->ssl, resp_code, REQ_EDIT_CHAT); // Send response indicating chat modification failure

        return 1;                                                   // Error
    }

    return 0; // Success
}

// Function to handle the editing of a chat
void handle_edit_chat(const cJSON *chat_info, t_server_utils *utils)
{
    // Initialize the database if not already initialized
    if (initialize_database(utils, REQ_EDIT_CHAT) != 0)
    {
        return;
    }

    const cJSON *chat_id, *new_name;

    // Extract and validate chat ID and new name
    if (extract_and_validate_chat_info(chat_info, &chat_id, &new_name, utils) != 0)
    {
        return;
    }

    // Check if the chat exists
    if (check_chat_existence(chat_id, utils) != 0)
    {
        return;
    }

    // Validate the new name length and format
    if (validate_new_name(new_name, utils) != 0)
    {
        return;
    }

    // Modify the chat name
    if (modify_chat_name(chat_id, new_name, utils) != 0)
    {
        return;
    }

    // Send success response
    send_server_response(utils->ssl, R_SUCCESS, REQ_EDIT_CHAT);
}
