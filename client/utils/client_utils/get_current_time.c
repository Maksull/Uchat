#include "../../inc/client.h"

// Function to get the current time in microseconds
unsigned long get_current_time()
{
    signed long dt = 0;
    // Getting the current date and time in the local timezone
    GDateTime *gtime = g_date_time_new_now_local();

    // Converting the date and time to Unix timestamp
    dt = g_date_time_to_unix(gtime);
    dt *= 1000000; // Converting seconds to microseconds
    dt += g_date_time_get_microsecond(gtime); // Adding microseconds to the timestamp
    dt /= 1000000; // Converting back to seconds

    // Freeing the memory allocated for GDateTime object
    g_date_time_unref(gtime);

    return dt; // Returning the current time in seconds
}
