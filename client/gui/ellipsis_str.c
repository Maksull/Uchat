#include "../inc/client.h"

// Function to add an ellipsis to a string if it exceeds a specified length
char *ellipsis_str(const char *str, int overflow_len)
{
    // Check if the length of the original string exceeds the specified overflow length
    if (mx_strlen(str) >= overflow_len)
    {
        // If it exceeds, create a substring of the original string up to the overflow length
        char *substring = mx_strndup(str, overflow_len);
        // Concatenate an ellipsis (...) to the substring
        char *result = mx_strjoin(substring, "...");
        // Free the memory allocated for the substring
        mx_strdel(&substring);
        
        return result;
    }
    else
    {
        // If the length of the original string is within the limit, duplicate the original string
        return mx_strdup(str);
    }
}
