#include "../../inc/client.h"

// Get the server response of a specified length
char *get_server_res(SSL *ssl, int length)
{
    // Buffer to store the response
    char buffer[SENT_DATA_LEN] = "";
    // Variable to track the number of bytes read
    int bytesRead = 0;

    // Loop until the specified length of data is read
    while (bytesRead < length)
    {
        // Read data from the SSL connection
        int bytes = SSL_read(ssl, &buffer[bytesRead], length - bytesRead);
        
        // Check for errors or if no data is available
        if (bytes <= 0)
        {
            // If there's no data available, continue the loop
            if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
            {
                continue;
            }
            // Log the error and return NULL
            logger(strerror(errno), ERROR_LOG);
            
            return NULL;
        }
        else if (bytes < length)
        {

            bytesRead += bytes;
        }
        else if (bytes == length)
        {

            bytesRead = bytes;
            break;
        }
    }

    // Null-terminate the buffer
    buffer[bytesRead] = '\0';

    // Return a duplicate of the buffer
    return mx_strdup(buffer);
}
