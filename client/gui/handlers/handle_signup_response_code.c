#include "../../inc/client.h"

// Function to handle successful signup response
static void handle_successful_signup(GtkWidget *signup_notify_label)
{
    set_notify_success_style(signup_notify_label, "You are successfully registered!");
    // Destroy the signup menu and build the login menu for the user to log in
    GtkWidget *signup_menu = get_widget_by_name_r(main_window, "signup_menu");
    GtkWidget *main_area = get_widget_by_name_r(main_window, "main_area");
    gtk_widget_destroy(signup_menu);
    build_login_menu(&main_area);
}

// Function to handle invalid input response for signup
static void handle_invalid_input_signup(GtkWidget *signup_notify_label)
{
    set_notify_error_style(signup_notify_label, get_res_str(R_INVALID_INPUT));
}

// Function to handle existing user response
static void handle_existing_user(GtkWidget *signup_notify_label)
{
    set_notify_error_style(signup_notify_label, get_res_str(R_USR_EXISTS));
}

// Function to handle invalid password length response
static void handle_invalid_password_length(GtkWidget *signup_notify_label)
{
    set_notify_error_style(signup_notify_label, get_res_str(R_PASS_LEN_INVALID));
}

// Function to handle signup response code
void handle_signup_res_code(int response_code, GtkWidget *signup_notify_label)
{
    switch (response_code)
    {
    case R_SUCCESS:
        handle_successful_signup(signup_notify_label);
        break;

    case R_INVALID_INPUT:
        handle_invalid_input_signup(signup_notify_label);
        break;

    case R_USR_EXISTS:
        handle_existing_user(signup_notify_label);
        break;

    case R_PASS_LEN_INVALID:
        handle_invalid_password_length(signup_notify_label);
        break;

    default:
        break;
    }
}
