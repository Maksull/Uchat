#include "../../inc/client.h"

// Function to construct the path to the avatar image file based on the color
static char *construct_avatar_path(int avatar_color, const char *avatar_type)
{
    char *path_base = avatar_type;
    char *tmp = mx_strjoin(path_base, mx_itoa(avatar_color + 1));
    char *path = mx_strjoin(tmp, ".png");
    mx_strdel(&tmp);
    return path;
}

// Function to load the avatar image and set it as the source for Cairo
static void load_and_set_avatar_image(cairo_t *cr, char *path, int width, int height)
{
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(path, width, height, FALSE, NULL);
    mx_strdel(&path);
    gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
    g_object_unref(G_OBJECT(pixbuf));
}

// Function to draw a rounded rectangle
static void draw_rounded_rectangle(cairo_t *cr)
{
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
}

// Function to draw user avatar
gboolean draw_user_avatar(GtkWidget *widget, cairo_t *cr, gpointer data)
{
    if (widget)
    { }
    int avatar_color = GPOINTER_TO_INT(data); // Extract the avatar color from the data

    char *path = construct_avatar_path(avatar_color, "client/data/img/user_avatars/avatar"); // Construct the path to the avatar image file
    load_and_set_avatar_image(cr, path, 27, 27);                                             // Load the avatar image and set it as the source for Cairo

    draw_rounded_rectangle(cr); // Draw a rounded rectangle to clip the avatar
    cairo_fill(cr);             // Fill the clipped area with the avatar image

    return FALSE;
}
