#include "../inc/client.h"

// Function to adds an ellipsis
char *ellipsis_str(const char *str, int overflow_len)
{
    char *tmp = NULL; // Temporary pointer for storing a substring
    char *result = NULL; // Pointer to the resulting string with an ellipsis

    // Check if the length of the original string exceeds the specified overflow length
    if (mx_strlen(str) >= overflow_len)
    {
        tmp = mx_strndup(str, overflow_len); // If it exceeds, create a substring of the original string up to the overflow length
        result = mx_strjoin(tmp, "..."); // Concatenate an ellipsis (...) to the substring
        mx_strdel(&tmp); // Free the memory allocated for the substring
    }
    else
    {
        result = mx_strdup(str); // If the length of the original string is within the limit, duplicate the original string
    }

    return result;
}
