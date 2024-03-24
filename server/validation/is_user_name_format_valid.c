#include "../inc/server.h"

// Check if the format of a username is valid
bool is_user_name_format_valid(const char *user_name) {
    // Use regex to check if the username matches the specified pattern
    return regex_for(user_name, "^[a-zA-Z0-9_-]*$");
}