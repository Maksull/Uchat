#include "../../inc/server.h"

// Function to retrieve chat ID by name from the database
static int get_chat_id(const char *chat_name, sqlite3 *db)
{
    char query[QUERY_LEN];
    sprintf(query, "SELECT `id` FROM `chats` WHERE `name` = '%s'", chat_name);

    sqlite3_stmt *sql_stmt = db_execute_sql_stmt(query, db);
    int chat_id = sqlite3_column_int64(sql_stmt, 0);
    sqlite3_finalize(sql_stmt);

    return chat_id;
}

// Function to insert a new member into the chat in the database
static int insert_member(int user_id, int chat_id, t_member_type member_type)
{
    char query[QUERY_LEN];
    sprintf(query,
            "INSERT INTO `members` (`user_id`, `chat_id`, `permissions`) VALUES('%d', '%d', '%d')",
            user_id, chat_id, member_type);

    if (db_execute_query(query) != 0)
    {
        return R_DB_FAILURE;
    }

    return R_SUCCESS;
}

// Original function refactored
int db_insert_member(const char *chat_name, t_member_type member_type, t_server_utils *utils)
{
    sqlite3 *db = open_db();
    int chat_id = get_chat_id(chat_name, db);
    sqlite3_close(db);

    if (chat_id < 0)
    {
        return R_DB_FAILURE; // Return failure code if chat ID retrieval fails
    }
    int user_id = utils->user->user_id;

    return insert_member(user_id, chat_id, member_type);
}
