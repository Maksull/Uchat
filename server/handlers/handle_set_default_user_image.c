#include "../inc/server.h" // Include necessary header file

// Function to handle setting default user image in the database
void handle_set_default_user_image(char *path, int id)
{
    // Open file to read
    int r;                        // Variable to hold return values for file operations
    FILE *fp = fopen(path, "rb"); // Open file in binary read mode
    if (fp == NULL)               // Check if file opening was unsuccessful
    {
        logger("Cannot open image file\n", ERROR_LOG); // Log error message
    }

    // Get length of file
    fseek(fp, 0, SEEK_END); // Move file pointer to end of file
    if (ferror(fp))         // Check for fseek() errors
    {
        logger("fseek() failed\n", ERROR_LOG); // Log error message
        if ((r = fclose(fp)) == EOF)           // Close file and check for errors
        {
            logger("Cannot close file\n", ERROR_LOG); // Log error message
        }
    }

    int flen = ftell(fp); // Get current position of file pointer (file size)
    if (flen == -1)       // Check if ftell() failed
    {
        logger("ftell() error", ERROR_LOG); // Log error message
        if ((r = fclose(fp)) == EOF)        // Close file and check for errors
        {
            logger("Cannot close file\n", ERROR_LOG); // Log error message
        }
    }

    fseek(fp, 0, SEEK_SET); // Move file pointer to beginning of file
    if (ferror(fp))         // Check for fseek() errors
    {
        logger("fseek() failed\n", ERROR_LOG); // Log error message
        if ((r = fclose(fp)) == EOF)           // Close file and check for errors
        {
            logger("Cannot close file\n", ERROR_LOG); // Log error message
        }
    }

    // Read data of image
    char *data = malloc(flen + 1);       // Allocate memory to hold file data
    int size = fread(data, 1, flen, fp); // Read file data into buffer
    if (ferror(fp))                      // Check for fread() errors
    {
        logger("fread() failed\n", ERROR_LOG); // Log error message
        if ((r = fclose(fp)) == EOF)           // Close file and check for errors
        {
            logger("Cannot close file\n", ERROR_LOG); // Log error message
        }
    }

    if ((r = fclose(fp)) == EOF) // Close file and check for errors
    {
        logger("Cannot close file\n", ERROR_LOG); // Log error message
    }

    // Open database
    sqlite3 *db;                         // SQLite database object
    int rc = sqlite3_open(DB_NAME, &db); // Open SQLite database
    if (rc != SQLITE_OK)                 // Check if database opening was unsuccessful
    {
        char error[100];                                                  // Error message buffer
        sprintf(error, "Cannot open database: %s\n", sqlite3_errmsg(db)); // Format error message
        logger(error, ERROR_LOG);                                         // Log error message
        sqlite3_close(db);                                                // Close database connection
    }

    // Write image to database
    sqlite3_stmt *pStmt;                                                    // Prepared statement object
    char *sql = malloc((unsigned)flen + 500);                               // Allocate memory for SQL query string
    bzero(sql, (unsigned)flen + 500);                                       // Clear memory for SQL query string
    sprintf(sql, "UPDATE `users` SET `image` = ? WHERE `id` = '%d' ;", id); // Construct SQL query

    rc = sqlite3_prepare(db, sql, -1, &pStmt, 0); // Prepare SQL statement
    if (rc != SQLITE_OK)                          // Check if preparation was unsuccessful
    {
        char error[100];                                                      // Error message buffer
        sprintf(error, "Cannot prepare statement: %s\n", sqlite3_errmsg(db)); // Format error message
        logger(error, ERROR_LOG);                                             // Log error message
    }

    sqlite3_bind_blob(pStmt, 1, data, size, SQLITE_STATIC); // Bind blob data to SQL parameter
    rc = sqlite3_step(pStmt);                               // Execute SQL statement
    if (rc != SQLITE_DONE)                                  // Check if execution was unsuccessful
    {
        char error[100];                                            // Error message buffer
        sprintf(error, "Execution failed: %s", sqlite3_errmsg(db)); // Format error message
        logger(error, ERROR_LOG);                                   // Log error message
    }

    sqlite3_finalize(pStmt); // Finalize prepared statement
    sqlite3_close(db);       // Close database connection
    free(sql);               // Free allocated memory for SQL query string
    free(data);              // Free allocated memory for file data
}
