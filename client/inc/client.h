#ifndef CLIENT_HEADER
#define CLIENT_HEADER

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#include <arpa/inet.h>

#include "../../libraries/libmx/inc/libmx.h"

#include "../../libraries/openssl/openssl/ssl.h"
#include "../../libraries/openssl/openssl/err.h"

#include "../../libraries/cjson/inc/cJSON.h"

typedef enum e_info_type
{
    INFO_LOG,
    ERROR_LOG
} t_info_type;

typedef enum e_avatar_color
{
    A_COLOR_FIRST,
    A_COLOR_SECOND,
    A_COLOR_THIRD,
    A_COLOR_FOURTH,
} t_avatar_color;

typedef struct s_user
{
    int user_id;
    char *name;
    char *password;
    char *avatar_path;
    t_avatar_color avatar_color;
} t_user;

typedef struct s_msg
{
    int message_id;
    int chat_id;
    int sender_id;
    char *sender_name;
    char *date_str;
    char *text;
    char *avatar_path;
    t_avatar_color avatar_color;
    struct s_msg *next;
} t_msg;

typedef struct s_chat
{
    int id;
    char *name;
    int permissions;
    t_msg *messages;
    t_msg *new_messages;
    t_msg *last_new_msg;
    int new_msg_count;
    t_avatar_color avatar_color;
    struct s_chat *next;
} t_chat;

typedef struct s_client_utils
{
    int server_fd;
    SSL *ssl;
    SSL_CTX *ctx;
    pthread_t th_reader;
    pthread_mutex_t lock;
    t_user *current_user;
    t_chat *current_chat;
    t_chat *chatlist;
    bool is_suspended;
} t_client_utils;

void handle_arg_errors(char **argv);
void handle_error(const char *error);

void init_ssl(SSL_CTX **ctx);
void connect_ssl(SSL **ssl, int *server_fd, SSL_CTX **ctx);

void connect_to_server(const char *ip_address, int port, int *server_fd, SSL_CTX **ctx, SSL **ssl);
void client_init(int server_fd, SSL *ssl, SSL_CTX *ctx);
void load_css();

void build_authorization_window();
GtkWidget *create_new_window(char *title, int width, int height, bool resizable);
void add_class(GtkWidget *widget, char *class_name);
void build_login_menu();

void *handle_server_updates(void *arg);

#endif