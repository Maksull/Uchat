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

typedef struct s_response
{
    t_response_code code;
    char *message;
} t_response;

static const t_response response_objs[] = {
    {R_SUCCESS, "Request handled successfully"},
    {R_DB_FAILURE, "A database error occurred when handling the request"},
    {R_JSON_FAILURE, "A json error occurred when handling the request"},
    {R_INVALID_INPUT, "The input was invalid"},
    {R_FILE_ERROR, "A file error occured"},
    {R_USR_EXISTS, "The user with this name already exists"},
    {R_USR_NOENT, "There's no user by that name"},
    {R_INVALID_PASS, "The entered password is incorrect"},
    {R_CHAT_EXISTS, "The chat with this name already exists"},
    {R_CHAT_NOENT, "The chat with this name doesn't exist"},
    {R_IS_CHAT_MEMBER, "You're already a member of this chat"},
    {R_ISNT_CHAT_MEMBER, "You're not a member of this chat"},
    {R_NO_CHAT_PERMS, "You don't have the permissions for this action"},
    {R_CHATS_TOTAL_REACHED, "You can't be a member of more than 15 chats"},
    {R_NAME_FORMAT_INVALID, "The name should contain only letters and digits"},
    {R_NAME_LEN_INVALID, "The name's length should be in a (4, 16) range"},
    {R_PASS_LEN_INVALID, "The password's length should be in a (8, 30) range"},
    {R_MSG_LEN_INVALID, "The message's length can't be greater than 1024 symbols"},
    {R_MSG_USR_NOENT, "Couldn't find this message's sender"},
};

void handle_arg_errors(char **argv);
void handle_error(const char *error);

void init_ssl(SSL_CTX **ctx);
void connect_ssl(SSL **ssl, int *server_fd, SSL_CTX **ctx);

void connect_to_server(const char *ip_address, int port, int *server_fd, SSL_CTX **ctx, SSL **ssl);
void client_init(int server_fd, SSL *ssl, SSL_CTX *ctx);
void load_css();
void on_crossing (GtkWidget *widget, GdkEventCrossing *event);
void set_field_error_style(GtkWidget *field);
void set_field_success_style(GtkWidget *field);
void set_notify_error_style(GtkWidget *notify_label, char *message);
void set_notify_success_style(GtkWidget *notify_label, char *message);
void add_class(GtkWidget *widget, char *class_name);
void remove_class(GtkWidget *widget, char *class_name);
char *get_server_response(SSL *ssl, int length);
char *get_response_str(t_response_code error_code);
t_response_code get_response_code(cJSON *json);
char *ellipsis_str(const char *str, int overflow_len);

char* send_and_recv_from_server(SSL *ssl, const char* json_str);
int send_to_server(SSL *ssl, const char *request_str);
char *recv_from_server(SSL *ssl);
void set_messages_as_read_for(t_chat *chat);

void *handle_server_updates(void *arg);
int handle_last_msg_id_request(int chat_id);
int handle_new_message(t_chat *curr_chat, int message_id, bool is_current);
void handle_get_msg_request(int chat_id, int message_id);
t_msg *handle_get_msg_response();
t_response_code handle_create_chat_request(const char *chat_name);
t_response_code handle_delete_account_request();
int handle_delete_chat_request(const char *chat_name);
void handle_delete_msg_request(int message_id);
t_response_code handle_edit_chat_request(int chat_id, const char *new_name);
void handle_edit_msg_request(int message_id, const char *new_msg_text);
t_response_code handle_edit_password_request(const char *new_pass, const char *old_pass);
t_response_code handle_edit_username_request(const char *new_name);
t_response_code handle_get_chat_msgs_request(int chat_id);
t_response_code handle_get_chat_msgs_response(const char *response_str);
t_response_code handle_get_chats_request();
t_response_code handle_get_chats_response(t_chat **chat_list, const char *response_str, bool is_search);
t_response_code handle_join_chat_request(const char *chat_name);
t_response_code handle_leave_chat_request(const char *chat_name);
t_response_code handle_login_request(const char *user_name, const char *user_password);
t_response_code handle_login_response(const char *response_str);
void handle_logout_request(bool is_client_exit);
t_chat *handle_search_chats_request(const char *search_str);
t_response_code handle_send_msg_response(const char *response_str, t_msg *sent_msg);
t_response_code handle_signup_request(const char *user_name, const char *user_password);
t_response_code handle_signup_response(const char *response_str);

void add_message(t_msg *message);
GtkWidget *get_widget_by_name_r(GtkWidget *container, char *name);
void update_chat_field();
void update_chatlist_item_info(t_chat *chat);
t_response_code add_chat_to_chatlist(cJSON *json, t_chat **chat_list, bool is_search);
t_response_code add_msg_to_msglist(cJSON *json);
t_response_code add_to_global_msglist(t_msg *new_msg);
void edit_global_messages(int message_id, const char *new_msg_text);
t_msg *get_msg_from_json(cJSON *json);
void modify_global_user(const char *new_name, const char *new_pass);
void recv_image_from_server(int *socket, unsigned char **buffer, size_t length);
void send_image_to_server(int *socket, void *buffer, size_t length);
void set_current_user(t_user **user, const cJSON *user_json);
void client_cleanup(bool is_client_exit);
t_avatar_color get_avatar_color();
unsigned long get_current_time();
char *get_string_time(unsigned long seconds);
void user_cleanup(t_user **user);

t_msg *mx_get_last_msg_node(t_msg *list);
int mx_msg_list_size(t_msg *list);
void mx_msg_push_back(t_msg **list, t_msg *new_node);

//HANDLE RESPONSE CODE
void handle_login_response_code(int error_code, GtkWidget *login_notify_label);
void handle_signup_response_code(int error_code, GtkWidget *signup_notify_label);
void handle_create_chat_response_code(int error_code, GtkWidget* entry_field, GtkWidget *create_chat_notify_label);
void handle_join_chat_response_code(int error_code, char *chat_name);
void handle_edit_password_response_code(int response_code, GtkWidget* entry_field, GtkWidget *change_password_notify_label);
void handle_edit_username_response_code(int response_code, GtkWidget* entry_field, GtkWidget *change_login_notify_label);
void handle_edit_chat_response_code(int response_code, GtkWidget* entry_field, GtkWidget *change_chat_name_notify_label);

//AUTH
void build_login_menu();
void build_signup_menu();

void build_chat_screen();
void build_leftbar(GtkWidget *chat_screen);

//LOG OUT
void logout_btn_click(GtkWidget *widget, gpointer data);
void build_confirm_logout_window(GtkWidget *widget, gpointer data);

//BUILD WINDOWS
GtkWidget* create_new_window(char *title, int width, int height, bool resizable);
GtkWidget *create_popup_window(int width, int height);
void destroy_popup_window(GtkWidget *widget, gpointer chat_screen);
void build_authorization_window();
void build_chat_window();

//CHATLIST
void add_chatlist_item(int id, char *chat_name, t_avatar_color avatar_color);
void build_chatlist_message(char *message);

//CHATLIST EVENTS
void clear_container(GtkWidget *container);
void update_chatlist();
void set_chatlist_item_active(GtkWidget *widget);
void set_current_chat(GtkWidget *chatlist_item);
void chatlist_item_on_click(GtkWidget *widget, gpointer data);
void activate_chat(GtkWidget *chatlist_item);
void build_start_messaging_label();

//SEARCH CHAT
void search_field_change_event(GtkWidget *widget, gpointer data);
void clear_search_field(GtkWidget *widget, gpointer entry_field);

//DELETE CHAT EVENTS
void delete_chat_btn_click(GtkWidget *widget, gpointer data);
void build_confirm_delete_chat_window(GtkWidget *widget, gpointer data);

//AUTH EVENTS
void signup_button_click(GtkWidget *widget, gpointer data);
void login_button_click(GtkWidget *widget, gpointer data);
void switch_to_signup_menu(GtkWidget *widget, gpointer data);
void switch_to_login_menu(GtkWidget *widget, gpointer data);
void focus_out_username_field(GtkWidget *widget, gpointer data);
void focus_out_password_field(GtkWidget *widget, gpointer data);
void focus_out_repassword_field(GtkWidget *widget, gpointer data);
bool is_empty_field(GtkWidget *field, GtkWidget *notify_label);

void build_create_chat_menu();

//CREATE CHAT MENU EVENTS
void popup_create_chat_menu(GtkWidget *widget, gpointer chat_screen);
void create_chat_btn_click(GtkWidget *widget, gpointer data);

//JOIN CHAT
void join_chat_event(GtkWidget *widget, GdkEventButton *event, gpointer data);
void add_join_chat_item(int id, char *chat_name, t_avatar_color avatar_color);

//DRAW AVATAR
gboolean draw_user_avatar(GtkWidget *widget, cairo_t *cr, gpointer data);
gboolean draw_message_avatar(GtkWidget *widget, cairo_t *cr, gpointer data);
gboolean draw_chat_avatar(GtkWidget *widget, cairo_t *cr, gpointer data);

void build_change_password_window(GtkWidget *widget, gpointer data);
void build_change_login_window(GtkWidget *widget, gpointer data);
void build_change_avatar_window(GtkWidget *widget, gpointer data);
void build_change_chat_name_window(GtkWidget *widget, gpointer data);

void leave_chat_btn_click(GtkWidget *widget, gpointer data);
void build_confirm_leave_chat_window(GtkWidget *widget, gpointer data);

void delete_account_btn_click(GtkWidget *widget, gpointer data);
void build_confirm_delete_account_window(GtkWidget *widget, gpointer data);
void login_or_password_is_invalid(GtkWidget *login_notify_label);

bool validate_name_field(GtkWidget *username_field, GtkWidget *username_notify_label);
bool validate_password_field(GtkWidget *password_field, GtkWidget *password_notify_label)
bool validate_repassword_field(GtkWidget *password_field, GtkWidget *repassword_field, GtkWidget *repassword_notify_label)

void focus_out_chat_name_field(GtkWidget *widget, gpointer data);
void focus_out_current_password_field(GtkWidget *widget, gpointer data);
void focus_out_login_field(GtkWidget *widget, gpointer data);
void focus_out_new_password_field(GtkWidget *widget, gpointer data);
void focus_out_re_new_password_field(GtkWidget *widget, gpointer data);

void build_rightbar_chat();
void delete_message(GtkWidget *widget, GdkEventButton *event, t_msg *message);
void edit_button_click(GtkWidget *widget, t_msg *message);
void edit_message(GtkWidget *widget, GdkEventButton *event, t_msg *message);
void scroll_to_end(GtkWidget *widget, gpointer data);
void send_button_click(GtkWidget *widget, gpointer new_message_field);

void build_found_chats(t_chat *chat_list);
void change_avatar_btn_click(GtkWidget *widget, gpointer data);
void change_chat_name_btn_click(GtkWidget *widget, gpointer data);
void change_login_btn_click(GtkWidget *widget, gpointer data);
void change_password_btn_click(GtkWidget *widget, gpointer data);
void destroy(GtkWidget *widget, gpointer data);

#endif