#include "../../inc/server.h"

// Function to open the image file
static FILE *open_image_file(const char *path)
{
    FILE *fp = fopen(path, "rb");
    if (!fp)
    {
        logger("Cannot open image file\n", ERROR_LOG);
    }
    
    return fp;
}

// Function to get the length of the image file
static int get_image_file_length(FILE *fp)
{
    fseek(fp, 0, SEEK_END);
    int flen = ftell(fp);
    if (flen == -1)
    {
        logger("ftell() error\n", ERROR_LOG);
    }
    fseek(fp, 0, SEEK_SET);

    return flen;
}

// Function to read data from the image file
static char *read_image_data(FILE *fp, int flen)
{
    char *data = malloc(flen);
    if (!data)
    {
        logger("Memory allocation failed\n", ERROR_LOG);

        return NULL;
    }

    int size = fread(data, 1, flen, fp);
    if (size != flen)
    {
        logger("Failed to read image data\n", ERROR_LOG);
        free(data);

        return NULL;
    }

    return data;
}

// Function to open the database
static sqlite3 *open_database()
{
    sqlite3 *db;
    int rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK)
    {
        char error[100];
        sprintf(error, "Cannot open database: %s\n", sqlite3_errmsg(db));
        logger(error, ERROR_LOG);
        sqlite3_close(db);

        return NULL;
    }

    return db;
}

// Function to write image data to the database
static int write_image_to_database(sqlite3 *db, int id, const char *data, int size)
{
    sqlite3_stmt *pStmt;
    char *sql = sqlite3_mprintf("UPDATE `users` SET `image` = ? WHERE `id` = '%d';", id);

    int rc = sqlite3_prepare_v2(db, sql, -1, &pStmt, NULL);
    if (rc != SQLITE_OK)
    {
        char error[100];
        sprintf(error, "Cannot prepare statement: %s\n", sqlite3_errmsg(db));
        logger(error, ERROR_LOG);
        sqlite3_free(sql);

        return rc;
    }

    sqlite3_bind_blob(pStmt, 1, data, size, SQLITE_STATIC);
    rc = sqlite3_step(pStmt);
    if (rc != SQLITE_DONE)
    {
        char error[100];
        sprintf(error, "Execution failed: %s\n", sqlite3_errmsg(db));
        logger(error, ERROR_LOG);
        sqlite3_finalize(pStmt);
        sqlite3_free(sql);

        return rc;
    }

    sqlite3_finalize(pStmt);
    sqlite3_free(sql);

    return rc;
}

// Function to handle setting default user image in the database
void handle_set_default_user_image(const char *path, int id)
{
    FILE *fp = open_image_file(path);
    if (!fp)
    {
        return;
    }

    int flen = get_image_file_length(fp);
    if (flen < 0)
    {
        fclose(fp);

        return;
    }

    char *data = read_image_data(fp, flen);
    fclose(fp);
    if (!data)
    {
        return;
    }

    sqlite3 *db = open_database();
    if (!db)
    {
        free(data);

        return;
    }

    if (write_image_to_database(db, id, data, flen) != SQLITE_OK)
    {
        sqlite3_close(db);
        free(data);

        return;
    }

    sqlite3_close(db);
    free(data);
}
