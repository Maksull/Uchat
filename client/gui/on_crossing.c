#include "../inc/client.h"

// Function to set the prelight state flag and change cursor to "hand1"
static void handle_enter_notify(GtkWidget *widget)
{
    gtk_widget_set_state_flags(widget, GTK_STATE_FLAG_PRELIGHT, TRUE); // Set prelight state flag to trigger :hover effect in CSS
    GdkDisplay *display = gtk_widget_get_display(widget);
    GdkCursor *cursor = gdk_cursor_new_from_name(display, "hand1"); // Change cursor to "hand1" (pointer)
    gdk_window_set_cursor(gtk_widget_get_window(widget), cursor);   // Set the cursor for the widget's window
    g_object_unref(cursor);                                         // Release the reference on the cursor
}

// Function to unset the prelight state flag and change cursor to "default"
static void handle_leave_notify(GtkWidget *widget)
{
    gtk_widget_unset_state_flags(widget, GTK_STATE_FLAG_PRELIGHT); // Remove prelight state flag
    GdkDisplay *display = gtk_widget_get_display(widget);
    GdkCursor *cursor = gdk_cursor_new_from_name(display, "default"); // Change cursor to "default"
    gdk_window_set_cursor(gtk_widget_get_window(widget), cursor);     // Set the cursor for the widget's window
    g_object_unref(cursor);                                           // Release the reference on the cursor
}

// Switch on crossing cursors
void on_crossing(GtkWidget *widget, GdkEventCrossing *event)
{
    switch (gdk_event_get_event_type((GdkEvent *)event))
    {
    case GDK_ENTER_NOTIFY:
        handle_enter_notify(widget);
        break;
    case GDK_LEAVE_NOTIFY:
        handle_leave_notify(widget);
        break;
    default:
        break;
    }
}
