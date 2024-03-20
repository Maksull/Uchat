#include "../inc/client.h"

// Function to draw user avatar
gboolean draw_user_avatar(GtkWidget *widget, cairo_t *cr, gpointer data)
{
    if (widget) { }
    int avatar_color = GPOINTER_TO_INT(data); // Extract the avatar color from the data

    // Construct the path to the avatar image file based on the color
    char *path = "client/data/img/user_avatars/avatar";
    char *tmp = mx_strjoin(path, mx_itoa(avatar_color + 1));
    path = mx_strjoin(tmp, ".png");
    mx_strdel(&tmp);

    // Load the avatar image and set it as the source for Cairo
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(path, 27, 27, FALSE, NULL);
    mx_strdel(&path);
    gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
    g_object_unref(G_OBJECT(pixbuf));

    // Draw a rounded rectangle to clip the avatar
    double x = 0;
    double y = 0;
    double width = 27;
    double height = 27;
    double aspect = 1.0;
    double corner_radius = height / 2.0;
    double radius = corner_radius / aspect;
    double degrees = 3.14159265358979 / 180.0;

    cairo_new_sub_path(cr);
    cairo_arc(cr, x + width - radius, y + radius, radius, -90 * degrees, 0 * degrees);
    cairo_arc(cr, x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
    cairo_arc(cr, x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
    cairo_arc(cr, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
    cairo_close_path(cr);

    // Fill the clipped area with the avatar image
    cairo_fill(cr);
    return FALSE;
}
