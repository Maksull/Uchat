#include "../../inc/client.h"

// Receive data from the server via SSL
char *receive_from_server(SSL *ssl)
{
    // Variable to store the number of bytes read
    int n_bytes = 0;
    // Buffer to store the received data
    char buffer[SENT_DATA_LEN] = "";

    // Read data from the SSL connection
    while ((n_bytes = SSL_read(ssl, buffer, SENT_DATA_LEN)) <= 0)
    {
        // If the number of bytes read is 0, return NULL (no data received)
        if (n_bytes == 0)
        {
            return NULL;
        }

        // If no data is available, continue the loop
        if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
        {
            continue;
        }
        // Log the error and return NULL
        logger(strerror(errno), ERROR_LOG);
        
        return NULL;
    }

    // Convert the buffer to an integer and use it to receive the server response
    return get_server_res(ssl, atoi(buffer));
}
