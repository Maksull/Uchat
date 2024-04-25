#include "../../inc/client.h"

// Function to add success class
void set_field_success_style(GtkWidget *field)
{
    remove_class(field, "input-field--danger"); // remove error class
    add_class(field, "input-field--success");   // add success class
}
