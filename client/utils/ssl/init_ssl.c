#include "../../inc/client.h"

// Initialize SSL context
void init_ssl(SSL_CTX **ctx)
{
    SSL_library_init(); // Initialize SSL library
    OpenSSL_add_all_algorithms(); // Load all SSL algorithms
    SSL_load_error_strings(); // Load SSL error strings

    *ctx = SSL_CTX_new(TLS_client_method()); // Create new SSL context for client
    if (*ctx == NULL) // Check if SSL context creation failed
    {
        handle_error(strerror(errno)); // Handle SSL context creation error
        exit(EXIT_FAILURE); // Exit with failure status
    }
}
