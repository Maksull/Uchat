#include "../../inc/client.h"

// Log information to the log file
void logger(const char *info, t_log_type type)
{
    // Open the log file in append mode
    FILE *fd = fopen(LOGFILE_NAME, "a+"); // Open the log file
    if (fd == NULL)
    {
        return;
    }
        
    // Write the log message to the log file
    fprintf(fd, "%s: ", type == ERROR_LOG ? "ERROR" : "INFO");
    fprintf(fd, "%s\n", info);
    fclose(fd); // Close the log file
}
