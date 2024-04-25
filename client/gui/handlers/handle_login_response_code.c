#include "../../inc/client.h"

// Function to handle successful login response
static void handle_successful_login(GtkWidget *login_notify_label)
{
    set_notify_success_style(login_notify_label, "You are successfully logged in!");
    build_chat_window(); // Proceed with building the chat window upon successful login
}

// Function to handle invalid input response
static void handle_invalid_input(GtkWidget *login_notify_label)
{
    set_notify_error_style(login_notify_label, get_res_str(R_INVALID_INPUT));
}

// Function to handle non-existent user response
static void handle_nonexistent_user(GtkWidget *login_notify_label)
{
    login_or_password_is_invalid(login_notify_label);
}

// Function to handle invalid password response
static void handle_invalid_password(GtkWidget *login_notify_label)
{
    login_or_password_is_invalid(login_notify_label); // Set error styles for invalid login or password
}

// Function to handle login response code
void handle_login_res_code(int response_code, GtkWidget *login_notify_label)
{
    switch (response_code)
    {
    case R_SUCCESS:
        handle_successful_login(login_notify_label);
        break;

    case R_INVALID_INPUT:
        handle_invalid_input(login_notify_label);
        break;

    case R_USR_NOENT:
        handle_nonexistent_user(login_notify_label);
        break;

    case R_INVALID_PASS:
        handle_invalid_password(login_notify_label);
        break;

    default:
        break;
    }
}
