#include "../../inc/server.h"

// Open the SQLite database
sqlite3 *open_db()
{
    sqlite3 *db; // SQLite database connection

    // Attempt to open the database
    if (sqlite3_open(DB_NAME, &db))
    {
        // If opening the database fails, log the error message and return NULL
        logger(strerror(errno), ERROR_LOG);
        return NULL;
    }

    return db; // Return the database connection
}
