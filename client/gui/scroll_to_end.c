#include "../inc/client.h"

// Function to handle scroll to the end
void scroll_to_end(GtkWidget *widget, gpointer data) {
    if(widget){}
    (void)data;

    // Get the scrollable wrap widget and the chat field widget
    GtkWidget *scrollable_wrap = get_widget_by_name_r(main_window, "scrollable_wrap");
    GtkWidget *chat_field = get_widget_by_name_r(main_window, "chat_field");

    GtkAdjustment *adj = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(scrollable_wrap)); // Get the vertical adjustment of the scrolled window
    // Get the upper limit and page size of the adjustment
    gdouble upper = gtk_adjustment_get_upper(adj);
    gdouble page_size = gtk_adjustment_get_page_size(adj);
    gtk_adjustment_set_value(adj, upper - page_size); // Set the adjustment value to scroll to the end of the chat field

    gtk_widget_show_all(chat_field); // Ensure the chat field is fully shown
}
