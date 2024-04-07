#include "../../inc/server.h"

// Initialize the database if it does not exist
int init_db()
{
    struct stat info;
    // Check if the database file exists
    if (stat(DB_NAME, &info) == 0)
    {
        // If the database file exists, return 0 (success)
        return 0;
    }

    sqlite3 *db = open_db(); // Open database connection

    // SQL query to create tables
    char *query =
        "CREATE TABLE `users` ("
        "`id` INTEGER PRIMARY KEY AUTOINCREMENT,"
        "`username` VARCHAR(32) NOT NULL,"
        "`password` VARCHAR(32) NOT NULL,"
        "`avatar_color` TINYINT NOT NULL,"
        "`image` BLOB);"

        "CREATE TABLE `chats` ("
        "`id` INTEGER PRIMARY KEY AUTOINCREMENT,"
        "`name` VARCHAR(32) NOT NULL,"
        "`date` INTEGER NOT NULL,"
        "`avatar_color` TINYINT NOT NULL);"

        "CREATE TABLE `members` ("
        "`id` INTEGER PRIMARY KEY AUTOINCREMENT,"
        "`user_id` INTEGER NOT NULL,"
        "`chat_id` INTEGER NOT NULL,"
        "`permissions` INTEGER NOT NULL);"

        "CREATE TABLE `messages` ("
        "`id` INTEGER PRIMARY KEY AUTOINCREMENT,"
        "`user_id` INTEGER NOT NULL,"
        "`chat_id` INTEGER NOT NULL,"
        "`text` VARCHAR(1024) NOT NULL,"
        "`date` INTEGER NOT NULL);";

    char *errmsg;
    // Execute SQL query to create tables
    if (sqlite3_exec(db, query, NULL, NULL, &errmsg))
    {
        // If query execution fails, log the error message and return 1 (failure)
        logger(errmsg, ERROR_LOG);
        sqlite3_close(db);
        return 1;
    }
    sqlite3_close(db);

    return 0;
}
