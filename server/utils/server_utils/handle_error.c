#include "../../inc/server.h"

// Function to handle and log errors
void handle_error(const char *err)
{
    char *err_str = mx_strjoin(err, "\n");
    mx_printerr(err_str);
    logger(err_str, ERROR_LOG);
    mx_strdel(&err_str);
}
