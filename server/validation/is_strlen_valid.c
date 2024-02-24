#include "../inc/server.h"

// Check if the length of a string is within a specified range
bool is_strlen_valid(const char *str, int min_len, int max_len)
{
    int str_len = mx_strlen(str);

    return (str_len >= min_len) && (str_len <= max_len);
}
