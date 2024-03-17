#include "../../inc/server.h"

// Check if a string matches a regular expression pattern
bool regex_for(const char *str, const char *pattern)
{
    regex_t regex;  // Regular expression structure
    int result = 0; // Result of regex operations

    // Compile the regular expression pattern
    if ((result = regcomp(&regex, pattern, 0)))
    {
        // If compilation fails, log an error message and return false
        logger("Could not compile regex", ERROR_LOG);
        return false;
    }

    // Execute the regular expression against the string
    result = regexec(&regex, str, 0, NULL, 0);

    regfree(&regex); // Free regular expression resources

    // Return true if there is a match, false otherwise
    return result != REG_NOMATCH;
}
