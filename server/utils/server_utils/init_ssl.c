#include "../../inc/server.h"

static void initialize_ssl_library()
{
    // Initialize SSL library
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
}

static void create_ssl_context(SSL_CTX **ctx)
{
    // Create new SSL context for TLS server
    *ctx = SSL_CTX_new(TLS_server_method());
    if (!*ctx)
    {
        handle_error(strerror(errno));
        exit(EXIT_FAILURE);
    }
}

// Function to initialize SSL
void init_ssl(SSL_CTX **ctx)
{
    // Paths to SSL certificate and private key files
    const char cert[] = "server/cert.crt";
    const char key[] = "server/key.key";

    // Initialize SSL library
    initialize_ssl_library();

    // Create new SSL context for TLS server
    create_ssl_context(ctx);

    // Load SSL certificate and private key
    load_certificate_and_key(*ctx, cert, key);
}
