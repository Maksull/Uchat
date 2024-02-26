#ifndef SERVER_HEADER
#define SERVER_HEADER

#include <arpa/inet.h>

#include <regex.h>

#include "../../libraries/libmx/inc/libmx.h"

#include "../../libraries/openssl/openssl/ssl.h"
#include "../../libraries/openssl/openssl/err.h"
#include "../../libraries/cjson/inc/cJSON.h"
#include "../../libraries/sqlite/inc/sqlite3.h"

#define SENT_DATA_LEN 4000
#define QUERY_LEN 500

#define MAX_NAME_INPUT_LEN 16
#define MIN_NAME_INPUT_LEN 4

#define MAX_PASS_INPUT_LEN  30
#define MIN_PASS_INPUT_LEN  8

#define MAX_CHATS_TOTAL 15

#define MAX_MSG_INPUT_LEN   1024
#define MIN_MSG_INPUT_LEN   1

#define DB_NAME "server_utils/database.db"
#define LOGFILE_NAME "server_utils/uchat.log"

// Enum for the type of info being logged
typedef enum e_log_type
{
    INFO_LOG,
    ERROR_LOG
} t_log_type;

typedef enum e_avatar_color {
    A_COLOR_FIRST,
    A_COLOR_SECOND,
    A_COLOR_THIRD,
    A_COLOR_FOURTH,
}            t_avatar_color;

typedef struct s_user
{
    int client_fd;
    SSL *ssl;
    int user_id;
    char *name;
    char *password;
    t_avatar_color avatar_color;
    struct s_user *next;
} t_user;


// Type for the type of a chat member
typedef enum e_member_type
{
    ADMIN_MEMBER,
    NORMAL_MEMBER,
} t_member_type;

typedef struct s_server_utils
{
    int client_socket;
    SSL *ssl;
    t_user *user;
} t_server_utils;

typedef void (*t_req_handler)(const cJSON *user_info, t_server_utils *utils);

// TODO: make a folder to contains utils
// Enum for the code of the server response to the client
typedef enum e_response_code
{
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
} t_response_code;

// Enum for the client request type
typedef enum e_request_type
{
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
} t_request_type;


// SERVER UTILS
void init_daemon();
void init_ssl(SSL_CTX **ctx);
void load_ssl_sertificate(SSL_CTX *ctx, const char *cert, const char *key);
void send_response_to(SSL *ssl, const char *response);
void send_server_response(SSL *ssl, t_response_code code, t_request_type req_type);
void client_cleanup(t_server_utils *utils, bool is_client_exit);
void handle_cli_arg_errors(char **argv);
int init_server_socket(struct sockaddr *server_address, socklen_t address_size);
void create_new_client(SSL *ssl, int client_socket);
void handle_error(const char *err);
void logger(const char *info, t_log_type info_type);

// HANDLERS
void *thread_handler(void *arg);

t_request_type handle_request_for(const char *req_args, t_server_utils *utils);
void handle_user_signup(const cJSON *user_info, t_server_utils *utils);
void handle_user_login(const cJSON *user_info, t_server_utils *utils);
t_request_type handle_user_logout(const cJSON *logout_info, t_server_utils *utils);

void handle_create_chat(const cJSON *chat_info, t_server_utils *utils);
void handle_delete_chat(const cJSON *chat_info, t_server_utils *utils);
void handle_edit_chat(const cJSON *chat_info, t_server_utils *utils);
void handle_get_chats(const cJSON *chat_info, t_server_utils *utils);
void handle_join_chat(const cJSON *chat_info, t_server_utils *utils);
void handle_leave_chat(const cJSON *chat_info, t_server_utils *utils);
void handle_search_chats(const cJSON *chat_info, t_server_utils *utils);

void handle_send_message(const cJSON *message_info, t_server_utils *utils);
void handle_edit_message(const cJSON *message_info, t_server_utils *utils);
void handle_get_chat_msgs(const cJSON *chat_info, t_server_utils *utils);
void handle_get_msg(const cJSON *msg_info, t_server_utils *utils);
void handle_last_msg_id(const cJSON *chat_info, t_server_utils *utils);
void handle_delete_message(const cJSON *message_info, t_server_utils *utils);
void handle_delete_account(const cJSON *chat_info, t_server_utils *utils);
void handle_edit_password(const cJSON *pass_info, t_server_utils *utils);
void handle_edit_username(const cJSON *user_info, t_server_utils *utils);

// DB
int init_database();
sqlite3 *open_database();
sqlite3_stmt *db_execute_stmt_for(const char *query, sqlite3 *db);
int db_execute_query(const char *query);
t_response_code db_add_user(const cJSON *user_info);
bool db_user_exists(const char *username);
char *db_get_username_by_id(int user_id);
int db_get_chat_id_by_name(const char *chat_name);
int db_get_chats_total(int user_id);
t_response_code db_edit_message(const cJSON *msg_json, t_server_utils *utils);
t_response_code db_insert_chat(const char *chat_name, int date, int avatar_color);
bool db_has_chat_perms(int user_id, int chat_id, t_member_type perms);
t_response_code db_delete_message(const cJSON *msg_json, t_server_utils *utils);
int db_insert_member(const char *chat_name, t_member_type member_type, t_server_utils *utils);
int db_delete_messages(int chat_id);
t_response_code db_insert_message(const cJSON *msg_json, int *message_id);
int db_delete_members(int chat_id);
t_response_code db_get_last_message_id(const cJSON *chat_info, int *last_msg_id);
t_response_code db_delete_member(int user_id, int chat_id);
t_response_code db_delete_chat(const char *chat_name, int chat_id);
bool db_chat_exists(int chat_id);
bool db_is_chat_member(int user_id, int chat_id);
t_response_code db_modify_chat_name(int chat_id, const char *new_name);
cJSON *db_get_chats_by_user_id(int user_id);
cJSON *db_get_message_by_id(const cJSON *msg_info);
cJSON *db_get_search_chats(const cJSON *chat_info, t_server_utils *utils);
cJSON *db_get_messages_array_json(int chat_id);
t_response_code db_delete_user(int user_id);
t_response_code db_delete_member_by_user_id(int user_id);
t_response_code db_modify_password(int user_id, const char *password);
t_response_code db_modify_user_name(int user_id, const char *new_name);

// UTILS
t_user *mx_create_user(int id, int client_fd, SSL *ssl);
void mx_clear_user(t_user **p);

cJSON *stmt_to_chat_json(sqlite3_stmt *stmt, bool is_for_search);
cJSON *stmt_to_message_json(sqlite3_stmt *stmt);

// VALIDATION
bool regex_for(const char *pattern, const char *str);
bool is_strlen_valid(const char *str, int min_len, int max_len);
bool is_user_name_format_valid(const char *user_name);

// An array of function pointers for request handlers
static const t_req_handler request_handlers[] = {
    handle_user_signup,
    handle_user_login,
    handle_create_chat,
    handle_delete_chat,
    handle_edit_chat,
    handle_get_chats,
    handle_join_chat,
    handle_leave_chat,
    handle_search_chats,
    handle_send_message,
    handle_edit_message,
    handle_get_chat_msgs,
    handle_get_msg,
    handle_last_msg_id,
    handle_delete_message,
    handle_delete_account,
    handle_edit_password,
    handle_edit_username,
    NULL};

#endif
