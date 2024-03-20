#include "../../inc/client.h"

// Function to convert seconds to formatted string time
char *get_string_time(unsigned long seconds)
{
    // Creating a GDateTime object from the provided Unix timestamp
    GDateTime *dt = g_date_time_new_from_unix_utc(seconds);
    // Converting the timestamp to local time
    GDateTime *new = g_date_time_to_local(dt);

    // Formatting the local time as a string with the specified format
    char *formatted_time = (char *)g_date_time_format(new, "%d.%m  %H:%M");

    // Freeing the memory allocated for GDateTime objects
    g_date_time_unref(dt);
    g_date_time_unref(new);

    // Returning the formatted time string
    return formatted_time;
}
