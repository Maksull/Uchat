#include "../../inc/client.h"

// Function to handle errors
void handle_error(const char *error)
{
    char *err_str = mx_strjoin(error, "\n"); // Concatenate error message with newline character
    mx_printerr(err_str); // Print error message to standard error
    logger(err_str, ERROR_LOG); // Log error message
    mx_strdel(&err_str); // Free allocated memory for error message string
}
