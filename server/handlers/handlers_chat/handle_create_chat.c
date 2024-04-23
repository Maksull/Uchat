#include "../../inc/server.h"

// Function to initialize the database and handle initialization errors
static int initialize_database(t_server_utils *utils, t_request_type request_type)
{
    if (init_db() != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, request_type);

        return 1; // Error
    }
    
    return 0; // Success
}

// Function to extract chat information from the JSON object and validate it
static int extract_and_validate_chat_info(const cJSON *chat_info, const cJSON **chat_name, const cJSON **date, const cJSON **av_color, t_server_utils *utils)
{
    *chat_name = cJSON_GetObjectItemCaseSensitive(chat_info, "name");
    *date = cJSON_GetObjectItem(chat_info, "date");
    *av_color = cJSON_GetObjectItem(chat_info, "avatar_color");

    // Validate chat information
    if (!cJSON_IsString(*chat_name) || !cJSON_IsNumber(*av_color) || !cJSON_IsNumber(*date))
    {
        send_server_response(utils->ssl, R_JSON_FAILURE, REQ_CREATE_CHAT); // Send response indicating JSON failure

        return 1;                                                          // Error
    }

    // Validate chat name length and format
    if (!is_strlen_valid((*chat_name)->valuestring, MIN_NAME_INPUT_LEN, MAX_NAME_INPUT_LEN))
    {
        send_server_response(utils->ssl, R_NAME_LEN_INVALID, REQ_CREATE_CHAT); // Send response indicating invalid name length

        return 1;                                                              // Error
    }

    if (!is_user_name_format_valid((*chat_name)->valuestring))
    {
        send_server_response(utils->ssl, R_NAME_FORMAT_INVALID, REQ_CREATE_CHAT); // Send response indicating invalid name format

        return 1;                                                                 // Error
    }

    return 0; // Success
}

// Function to handle the insertion of a new chat into the database
static int insert_new_chat(const cJSON *chat_name, const cJSON *date, const cJSON *av_color, t_server_utils *utils)
{
    t_response_code resp_code = db_insert_chat(chat_name->valuestring, date->valueint, av_color->valueint);
    if (resp_code != R_SUCCESS)
    {
        send_server_response(utils->ssl, resp_code, REQ_CREATE_CHAT); // Send response indicating chat insertion failure

        return 1;                                                     // Error
    }

    return 0; // Success
}

// Function to handle the insertion of the current user as an admin member of the chat
static int insert_current_user_as_admin(const cJSON *chat_name, t_server_utils *utils)
{
    if (db_insert_member(chat_name->valuestring, ADMIN_MEMBER, utils) != 0)
    {
        send_server_response(utils->ssl, R_DB_FAILURE, REQ_CREATE_CHAT); // Send response indicating member insertion failure

        return 1;                                                        // Error
    }

    return 0; // Success
}

// Function to handle the creation of a new chat
void handle_create_chat(const cJSON *chat_info, t_server_utils *utils)
{
    // Initialize the database if not already initialized
    if (initialize_database(utils, REQ_CREATE_CHAT) != 0)
    {
        return;
    }

    const cJSON *chat_name, *date, *av_color;

    // Extract and validate chat information
    if (extract_and_validate_chat_info(chat_info, &chat_name, &date, &av_color, utils) != 0)
    {
        return;
    }

    // Check if maximum total chats limit reached
    if (db_get_chats_total(utils->user->user_id) >= MAX_CHATS_TOTAL)
    {
        send_server_response(utils->ssl, R_CHATS_TOTAL_REACHED, REQ_CREATE_CHAT); // Send response indicating maximum chats reached
        
        return;
    }

    // Insert new chat into the database
    if (insert_new_chat(chat_name, date, av_color, utils) != 0)
    {
        return;
    }

    // Insert the current user as an admin member of the chat
    if (insert_current_user_as_admin(chat_name, utils) != 0)
    {
        return;
    }

    // Send success response
    send_server_response(utils->ssl, R_SUCCESS, REQ_CREATE_CHAT);
}
