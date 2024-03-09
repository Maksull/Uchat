#include "../inc/client.h"

// Switch on crossing cursors
void on_crossing(GtkWidget *widget, GdkEventCrossing *event)
{
    GdkDisplay *display = gtk_widget_get_display(widget);
    GdkCursor *cursor = NULL;

    switch (gdk_event_get_event_type((GdkEvent*)event))
    {
        case GDK_ENTER_NOTIFY:
            gtk_widget_set_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT, TRUE); // Set prelight state flag to trigger :hover effect in CSS
            cursor = gdk_cursor_new_from_name (display, "hand1"); // Change cursor to "hand1" (pointer)
            break;

        case GDK_LEAVE_NOTIFY:
            gtk_widget_unset_state_flags(GTK_WIDGET(widget), GTK_STATE_FLAG_PRELIGHT); // Remove prelight state flag
            cursor = gdk_cursor_new_from_name (display, "default"); // Change cursor to "default"
            break;

        default:
            break;
    }

    gdk_window_set_cursor (gtk_widget_get_window(widget), cursor); // Set the cursor for the widget's window

    g_object_unref(cursor); // Release the reference on the cursor
}
