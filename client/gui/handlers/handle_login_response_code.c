#include "../../inc/client.h"

// Function to handle login response code
void handle_login_res_code(int response_code, GtkWidget *login_notify_label)
{
    switch (response_code)
    {
        case R_SUCCESS:
            set_notify_success_style(login_notify_label, "You are successful loginned!");
            build_chat_window(); // Proceed with building the chat window upon successful login
            break;

        case R_INVALID_INPUT:
            set_notify_error_style(login_notify_label, get_res_str(R_INVALID_INPUT));
            break;

        case R_USR_NOENT:
            login_or_password_is_invalid(login_notify_label);
            break;

        case R_INVALID_PASS:
            login_or_password_is_invalid(login_notify_label); // Set error styles for invalid login or password
            break;

        default:
            break;
    }
}
