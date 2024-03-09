#include "../inc/client.h"

// Function to add error style
void set_field_error_style(GtkWidget *field)
{
    remove_class(field, "input-field--success"); // removing success styles
    add_class(field, "input-field--danger"); // adding error styles
}
