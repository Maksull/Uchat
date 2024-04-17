#include "../../inc/client.h"

// Function to create a JSON object for deleting a message request
static cJSON *create_delete_msg_json(int message_id) {
    // Create JSON object for the request
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", REQ_DELETE_MESSAGE);
    cJSON_AddNumberToObject(json, "id", message_id);
    cJSON_AddNumberToObject(json, "user_id", utils->current_user->user_id);
    cJSON_AddNumberToObject(json, "chat_id", utils->current_chat->id);

    return json;
}

// Function to edit global messages
static void edit_global_messages(int message_id)
{
    // Check if the message to be deleted is the last message
    bool is_last_msg = message_id == utils->current_chat->last_new_msg->message_id;
    // Pop the message with the given message_id from the current chat's messages list
    mx_msg_pop_id(&utils->current_chat->messages, message_id);
    // If the deleted message was the last message, update the last_new_msg pointer
    if (is_last_msg)
    {
        if (mx_msg_list_size(utils->current_chat->messages) == 0)
        {
            utils->current_chat->last_new_msg = NULL;
        }
        else
        {
            utils->current_chat->last_new_msg = mx_get_last_msg_node(utils->current_chat->messages);
        }
        // Update the chatlist item info
        update_chatlist_item_info(utils->current_chat);
    }
}

// Function to handle delete message request
void handle_delete_msg_req(int message_id)
{
    // Set the client as suspended
    utils->is_suspended = true;

    // Create JSON object for the request
    cJSON *json = create_delete_msg_json(message_id);
    char *json_str = cJSON_PrintUnformatted(json);
    cJSON_Delete(json);

    // Send request to server and receive response
    char *response = send_and_receive_from_server(utils->ssl, json_str);
    // Handle the server response
    int error_code = handle_server_res(response);
    // Log the response
    logger(get_res_str(error_code), error_code == R_SUCCESS ? INFO_LOG : ERROR_LOG);

    // If response is successful, edit global messages
    if (error_code == R_SUCCESS)
    {
        edit_global_messages(message_id);
    }

    // Free memory
    free(json_str);
    free(response);
    // Set the client as not suspended
    utils->is_suspended = false;
}
