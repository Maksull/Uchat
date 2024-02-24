#ifndef SERVER_HEADER
#define SERVER_HEADER

#include "../../libraries/libmx/inc/libmx.h"

#include "../../libraries/openssl/openssl/ssl.h"
#include "../../libraries/openssl/openssl/err.h"

#include "../../libraries/cjson/inc/cJSON.h"

#define SENT_DATA_LEN   4000

typedef struct s_user
{
    // TODO
} t_user;

typedef struct s_server_utils
{
    int client_socket;
    SSL *ssl;
    t_user *user;
} t_server_utils;

// TODO: make a folder to contains utils
// Enum for the code of the server response to the client
typedef enum e_response_code {
    R_SUCCESS,
    R_DB_FAILURE,
    R_JSON_FAILURE,
    R_INVALID_INPUT,
    R_FILE_ERROR,
    
    R_USR_EXISTS,
    R_USR_NOENT,
    R_INVALID_PASS,
    R_CHAT_EXISTS,
    R_CHAT_NOENT,
    R_IS_CHAT_MEMBER,
    R_ISNT_CHAT_MEMBER,
    R_NO_CHAT_PERMS,
    R_CHATS_TOTAL_REACHED,
    R_NAME_FORMAT_INVALID,
    R_NAME_LEN_INVALID,
    R_PASS_LEN_INVALID,
    R_MSG_LEN_INVALID,

    R_MSG_USR_NOENT,
}            t_response_code;

// Enum for the client request type
typedef enum e_request_type {
    REQ_USR_SIGNUP,
    REQ_USR_LOGIN,
    REQ_CREATE_CHAT,
    REQ_JOIN_CHAT,
    REQ_SEND_MESSAGE,
    REQ_LEAVE_CHAT,
    REQ_DELETE_CHAT,
    REQ_DELETE_MESSAGE,
    REQ_EDIT_MESSAGE,

    REQ_GET_CHATS,
    REQ_GET_CHAT_MSGS,
    REQ_GET_MSG,
    REQ_LAST_MSG_ID,
    REQ_SEARCH_CHATS,
    REQ_EDIT_CHAT,
    REQ_EDIT_USERNAME,
    REQ_EDIT_PASSWORD,
    REQ_DELETE_ACCOUNT,
    
    REQ_USR_LOGOUT,
    REQ_CLIENT_EXIT,
}            t_request_type;

// SERVER UTILS

void init_daemon();
void init_ssl(SSL_CTX **ctx);
void load_ssl_sertificate(SSL_CTX *ctx, const char *cert, const char *key);
void send_response_to(SSL* ssl, const char* response);
void send_server_response(SSL* ssl, t_response_code code, t_request_type req_type);
void client_cleanup(t_server_utils* utils, bool is_client_exit);
void handle_cli_arg_errors(char **argv);
int init_server_socket(struct sockaddr *server_address, socklen_t address_size);
void create_new_client(SSL *ssl, int client_socket);
void handle_error(const char *err);

// USER UTILS

void mx_clear_user(t_user** p);

// REQUEST HANDLERS

t_request_type handle_request_for(const char* req_args, t_server_utils* utils);
t_request_type get_request_type(cJSON* json);
t_request_type handle_usr_logout(const cJSON* logout_info, t_server_utils* utils);

// THREADS

void *thread_handler(void *arg);

#endif