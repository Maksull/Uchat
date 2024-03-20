#include "../../inc/client.h"

// Check if command line arguments are valid
void handle_arg_errors(char **argv)
{
    if (argv[1] == NULL || argv[2] == NULL) // Check if IP address or port number is missing
    {
        mx_printerr("usage: ./uchat [ip] [port]\n"); // Print usage message to standard error
        exit(EXIT_FAILURE); // Exit program with failure status
    }
}
