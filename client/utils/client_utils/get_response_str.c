#include "../../inc/client.h"

// Get the response string associated with a response code
char *get_response_str(t_response_code error_code)
{
    // Calculate the size of the response_objs array
    size_t arr_size = sizeof(response_objs) / sizeof(response_objs[0]);

    // Iterate through the array
    for (size_t i = 0; i < arr_size; ++i)
    {
        // If the response code matches, return the corresponding message
        if (response_objs[i].code == error_code)
        {
            return response_objs[i].message;
        }
    }
    
    // If no matching response code is found, return NULL
    return NULL;
}
