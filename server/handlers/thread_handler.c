#include "../inc/server.h"

// This function retrieves the client request from the SSL connection
static char* get_client_request(SSL* ssl, int length) {

    char buffer[SENT_DATA_LEN] = "";

    int bytesRead = 0;

    while (bytesRead < length) {

        // Read data from the SSL connection into the buffer
        int bytes = SSL_read(ssl, &buffer[bytesRead], length - bytesRead);

        // Check if an error occurred during the read operation
        if (bytes <= 0) {
            if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
                continue; 
            }
            return NULL;
        } else if (bytes < length) {
            bytesRead += bytes;
        } else if (bytes == length) {
            bytesRead = bytes;
            break;
        }
    }

    buffer[bytesRead] = '\0';

    // Return a duplicate of the buffer string
    return mx_strdup(buffer);
}

//  Function reads data from the client through the provided SSL connection
static char* read_client_data(SSL *ssl) {

    char buffer[SENT_DATA_LEN];

    int n_bytes = 0;

    // Reading data from the client
    while ((n_bytes = SSL_read(ssl, buffer, SENT_DATA_LEN)) <= 0) {
        
        // Check if the error is due to the operation would block or no data available
        if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
            continue; 
        }
        
        return NULL;
    
    }

    // Process the received data and return the client request
    return get_client_request(ssl, atoi(buffer));
}

//Function for creating thread  for handling client requests.
void* thread_handler(void* arg) {

    t_server_utils *server_utils = (t_server_utils*)arg;

    while (1) {

        char* request_str = NULL;

        // Read data from the client using SSL connection
        if (!(request_str = read_client_data(server_utils->ssl)))
            continue; 

        // Handle the received request and determine its type
        t_request_type req_type = handle_request_for(request_str, server_utils);

        // Check if the client requested to exit
        if (req_type == REQ_CLIENT_EXIT) {
            mx_strdel(&request_str);
            break;
        }

        mx_strdel(&request_str);

    }

    // Detach the thread upon completion
    pthread_detach(pthread_self());

    return NULL;
}