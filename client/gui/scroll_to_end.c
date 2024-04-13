#include "../inc/client.h"

// Function to get the vertical adjustment of a scrolled window
static GtkAdjustment *get_vertical_adjustment(GtkWidget *scrolled_window)
{
    return gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(scrolled_window));
}

// Function to scroll to the end of a scrolled window
static void scroll_to_end_of_window(GtkAdjustment *adjustment)
{
    gdouble upper = gtk_adjustment_get_upper(adjustment);         // Get the upper limit of the adjustment
    gdouble page_size = gtk_adjustment_get_page_size(adjustment); // Get the page size of the adjustment
    gtk_adjustment_set_value(adjustment, upper - page_size);      // Set the adjustment value to scroll to the end
}

// Function to get a widget by name within the main window
static GtkWidget *get_widget_by_name_in_main_window(const gchar *name)
{
    return get_widget_by_name_r(main_window, name);
}

// Function to handle scroll to the end
static void scroll_to_end(GtkWidget *widget, gpointer data)
{
    if (widget)
    { }
    (void)data;

    // Get the scrollable wrap widget and the chat field widget
    GtkWidget *scrollable_wrap = get_widget_by_name_in_main_window("scrollable_wrap");
    GtkWidget *chat_field = get_widget_by_name_in_main_window("chat_field");

    GtkAdjustment *adj = get_vertical_adjustment(scrollable_wrap); // Get the vertical adjustment of the scrolled window
    scroll_to_end_of_window(adj);                                  // Scroll to the end of the chat field

    gtk_widget_show_all(chat_field); // Ensure the chat field is fully shown
}
