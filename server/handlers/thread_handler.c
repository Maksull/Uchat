#include "../inc/server.h"

// Read data from the SSL connection into the buffer
static int read_ssl_data(SSL *ssl, char *buffer, int length)
{
    int bytesRead = 0;

    while (bytesRead < length)
    {
        int bytes = SSL_read(ssl, &buffer[bytesRead], length - bytesRead);

        if (bytes <= 0)
        {
            if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
            {
                continue;
            }
            
            return -1; // Error or no data available
        }
        else
        {
            bytesRead += bytes;
        }
    }

    return bytesRead;
}

// This function retrieves the client request from the SSL connection
static char *get_client_request(SSL *ssl, int length)
{
    char buffer[SENT_DATA_LEN] = "";

    int bytesRead = read_ssl_data(ssl, buffer, length);

    if (bytesRead <= 0)
    {
        return NULL; // Error reading or no data received
    }

    buffer[bytesRead] = '\0';

    // Return a duplicate of the buffer string
    return strdup(buffer);
}

// Function to read data from the SSL connection
static int read_client_ssl_data(SSL *ssl, char *buffer, int length)
{
    int n_bytes = 0;

    // Reading data from the SSL connection
    while ((n_bytes = SSL_read(ssl, buffer, length)) <= 0)
    {
        // Check if the error is due to the operation would block or no data available
        if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
        {
            continue;
        }

        return -1; // Error reading or no data available
    }

    return n_bytes;
}

// Function to read client data through the provided SSL connection
static char *read_client_data(SSL *ssl)
{
    char buffer[SENT_DATA_LEN];

    int n_bytes = read_client_ssl_data(ssl, buffer, SENT_DATA_LEN);

    if (n_bytes <= 0)
    {
        return NULL; // Error reading or no data available
    }

    // Process the received data and return the client request
    return get_client_request(ssl, atoi(buffer));
}

// Define a new function to handle client requests
static void handle_client_requests(t_server_utils *server_utils)
{
    while (1)
    {
        char *request_str = NULL;

        // Read data from the client using SSL connection
        if (!(request_str = read_client_data(server_utils->ssl)))
        {
            continue;
        }

        // Handle the received request and determine its type
        t_request_type req_type = handle_request_for(request_str, server_utils);

        // Check if the client requested to exit
        if (req_type == REQ_CLIENT_EXIT)
        {
            mx_strdel(&request_str);
            break;
        }

        mx_strdel(&request_str);
    }
}

// Function for creating thread  for handling client requests.
void *thread_handler(void *arg)
{
    t_server_utils *server_utils = (t_server_utils *)arg;

    // Handle client requests
    handle_client_requests(server_utils);

    // Detach the thread upon completion
    pthread_detach(pthread_self());

    return NULL;
}
