#include "../inc/client.h"

// Function to handle signup response code
void handle_signup_response_code(int response_code, GtkWidget *signup_notify_label)
{
    switch (response_code)
    {
        case R_SUCCESS:
            set_notify_success_style(signup_notify_label, "You are successful registered!");
            // Destroy the signup menu and build the login menu for the user to log in
            GtkWidget *signup_menu = get_widget_by_name_r(main_window, "signup_menu");
            GtkWidget *main_area = get_widget_by_name_r(main_window, "main_area");
            gtk_widget_destroy(signup_menu);
            build_login_menu(&main_area);
            break;

        case R_INVALID_INPUT:
            set_notify_error_style(signup_notify_label, get_response_str(R_INVALID_INPUT));
            break;

        case R_USR_EXISTS:
            set_notify_error_style(signup_notify_label, get_response_str(R_USR_EXISTS));
            break;

        case R_PASS_LEN_INVALID:
            set_notify_error_style(signup_notify_label, get_response_str(R_PASS_LEN_INVALID));
            break;

        default:
            break;
    }
}
