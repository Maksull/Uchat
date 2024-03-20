#include "../inc/client.h"

// Function to set notify error style
void set_notify_error_style(GtkWidget *notify_label, char *message)
{
    remove_class(notify_label, "notify-label--success");  // remove success class
    add_class(notify_label, "notify-label--danger");      // add error class
    gtk_label_set_text(GTK_LABEL(notify_label), message); // set label text
}
