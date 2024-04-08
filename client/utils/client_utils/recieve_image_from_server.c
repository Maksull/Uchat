#include "../../inc/client.h"

// Function to receive an image from the server
void recieve_image_from_server(int *socket, unsigned char **buffer, size_t length)
{
    unsigned char *ptr = *buffer; // Pointer to the start of the buffer

    // Continue receiving data until the entire image is received
    while (length > 0)
    {
        int i = recv(*socket, ptr, length, 0); // Receive data
        ptr += i;                              // Move the pointer forward by the number of bytes received
        length -= i;                           // Decrease the remaining length
    }
}
