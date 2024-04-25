#include "../../inc/server.h"

// Function to load SSL certificate from file
static void load_ssl_certificate_file(SSL_CTX *ctx, const char *cert)
{
    if (SSL_CTX_use_certificate_file(ctx, cert, SSL_FILETYPE_PEM) <= 0)
    {
        handle_error(strerror(errno));
        exit(EXIT_FAILURE);
    }
}

// Function to load SSL private key from file
static void load_ssl_private_key_file(SSL_CTX *ctx, const char *key)
{
    if (SSL_CTX_use_PrivateKey_file(ctx, key, SSL_FILETYPE_PEM) <= 0)
    {
        handle_error(strerror(errno));
        exit(EXIT_FAILURE);
    }
}

// Function to verify that the private key matches the certificate
static void verify_ssl_private_key_match(SSL_CTX *ctx)
{
    if (!SSL_CTX_check_private_key(ctx))
    {
        handle_error(strerror(errno));
        exit(EXIT_FAILURE);
    }
}

// Function to load SSL certificate and private key
void load_ssl_certificate(SSL_CTX *ctx, const char *cert, const char *key)
{
    load_ssl_certificate_file(ctx, cert);
    load_ssl_private_key_file(ctx, key);
    verify_ssl_private_key_match(ctx);
}
