#include "../../inc/client.h"

// Send a request string to the server
int send_to_server(SSL *ssl, const char *request_str)
{
    // Calculate the length of the request string
    int req_len = mx_strlen(request_str);
    // Convert the length to a string
    char *len_str = mx_itoa(req_len);
    // Write the length string to the SSL connection
    SSL_write(ssl, len_str, mx_strlen(len_str));
    // Variable to store SSL error code
    unsigned long err = 0;
    // Send the request string to the server
    while (SSL_write(ssl, request_str, req_len) == -1)
    {
        // If there is an SSL error, print the error message
        if ((err = ERR_get_error()))
        {
            printf("error is: %s\nreason -- %s\n", ERR_error_string(err, NULL), ERR_reason_error_string(err));
        }
        // Free the length string
        mx_strdel(&len_str);
        
        return 1;
    }
    // Free the length string
    mx_strdel(&len_str);

    return 0;
}
