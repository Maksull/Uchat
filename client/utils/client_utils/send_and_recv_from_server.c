#include "../../inc/client.h"

// Send a JSON string to the server and receive a response
char *send_and_recv_from_server(SSL *ssl, const char *json_str)
{
    // Send the JSON string to the server
    if (send_to_server(ssl, json_str) != 0)
    {
        return NULL;
    }

    // Receive the response from the server
    return recv_from_server(ssl);
}
