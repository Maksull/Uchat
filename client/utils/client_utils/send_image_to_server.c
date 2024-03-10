#include "../../inc/client.h"

void send_image_to_server(int *socket, void *buffer, size_t length)
{
    unsigned char *ptr = *buffer; // Pointer to the start of the buffer

    // Continue receiving data until the entire image is received
    while (length > 0)
    {
        int i = send(*socket, ptr, length, 0); // Send data
        ptr += i;                              // Move the pointer forward by the number of bytes received
        length -= i;                           // Decrease the remaining length
    }
}
