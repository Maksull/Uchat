#include "../../inc/server.h"

// Function to handle command-line argument errors
void handle_cli_arg_errors(char **argv)
{
    // Check if port number is provided as command line argument
    if (argv[1] == NULL)
    {
        mx_printerr("usage: ./uchat_server [port]\n");
        exit(EXIT_FAILURE);
    }
}
