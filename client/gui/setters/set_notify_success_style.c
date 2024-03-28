#include "../../inc/client.h"

// Function to set notify success style
void set_notify_success_style(GtkWidget *notify_label, char *message)
{
    remove_class(notify_label, "notify-label--danger");   // remove error style
    add_class(notify_label, "notify-label--success");     // add success style
    gtk_label_set_text(GTK_LABEL(notify_label), message); // set text to the label
}
