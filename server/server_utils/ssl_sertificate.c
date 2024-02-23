#include "../../inc/server.h"

// Function to load SSL certificate and private key
void load_ssl_sertificate(SSL_CTX *ctx, const char *cert, const char *key)
{
    // Load SSL certificate from file
    if (SSL_CTX_use_certificate_file(ctx, cert, SSL_FILETYPE_PEM) <= 0)
    {
        handle_error(strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Load SSL private key from file
    if (SSL_CTX_use_PrivateKey_file(ctx, key, SSL_FILETYPE_PEM) <= 0)
    {
        handle_error(strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Verify that the private key matches the certificate
    if (!SSL_CTX_check_private_key(ctx))
    {
        handle_error(strerror(errno));
        exit(EXIT_FAILURE);
    }
}