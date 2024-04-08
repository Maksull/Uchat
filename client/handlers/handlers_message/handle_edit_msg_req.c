#include "../../inc/client.h"

// Function to edit global messages
static void edit_global_messages(int message_id, const char *new_msg_text)
{
    // Find the message to edit by its ID in the current chat's message list
    t_msg *msg_to_edit = mx_get_msg_by_id(utils->current_chat->messages, message_id);
    if (msg_to_edit)
    {
        // Free the current text of the message and allocate memory for the new text
        mx_strdel(&msg_to_edit->text);
        msg_to_edit->text = mx_strdup(new_msg_text);

        // Update the chat list item information
        update_chatlist_item_info(utils->current_chat);
    }
}


// Function to handle edit message request
void handle_edit_msg_req(int message_id, const char *new_msg_text)
{
    // Set the client as suspended
    utils->is_suspended = true;

    // Create JSON object for the request
    cJSON *json = cJSON_CreateObject();
    cJSON_AddNumberToObject(json, "type", REQ_EDIT_MESSAGE);
    cJSON_AddNumberToObject(json, "id", message_id);
    cJSON_AddStringToObject(json, "text", new_msg_text);
    cJSON_AddNumberToObject(json, "user_id", utils->current_user->user_id);
    cJSON_AddNumberToObject(json, "chat_id", utils->current_chat->id);
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
        edit_global_messages(message_id, new_msg_text);
    }

    // Free memory
    free(json_str);
    free(response);
    // Set the client as not suspended
    utils->is_suspended = false;
}
