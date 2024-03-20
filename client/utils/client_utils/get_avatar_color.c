#include "../../inc/client.h"

// Function to generate a random avatar color
t_avatar_color get_avatar_color()
{
    // Generating a random number within the range of available avatar colors
    return rand() % (A_COLOR_FOURTH + 1);
}
