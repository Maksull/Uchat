#include "../../inc/server.h"

// Check if the database file exists
int does_db_exist()
{
    struct stat info;
    return stat(DB_NAME, &info) == 0;
}

// Create database tables
int create_db_tables(sqlite3 *db)
{
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
        logger(errmsg, ERROR_LOG);

        return 1;
    }

    return 0;
}

// Initialize the database if it does not exist
int init_db()
{
    // Check if the database file exists
    if (does_db_exist())
    {
        return 0; // Database already exists
    }

    sqlite3 *db = open_db(); // Open database connection

    // Create tables in the database
    if (create_db_tables(db))
    {
        sqlite3_close(db);

        return 1; // Failed to create tables
    }

    sqlite3_close(db);

    return 0; // Database initialization successful
}
