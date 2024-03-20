#include "../../inc/server.h"

// Create a new user structure
t_user *mx_create_user(int id, int client_fd, SSL *ssl)
{
    // Allocate memory for the new user structure
    t_user *new_node = malloc(sizeof(t_user));
    if (new_node == NULL)
    {
        return NULL;
    }

    // Initialize the fields of the new user structure
    new_node->user_id = id;
    new_node->client_fd = client_fd;
    new_node->name = NULL;
    new_node->password = NULL;
    new_node->ssl = ssl;
    new_node->next = NULL;

    return new_node;
}
