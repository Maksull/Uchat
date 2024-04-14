#include "../../inc/client.h"

// Function to remove "active" class from all chat list items
static void remove_active_class_from_chatlist_items(GtkWidget *chatlist_container)
{
    GList *children = gtk_container_get_children(GTK_CONTAINER(chatlist_container));
    while (children)
    {
        remove_class(GTK_WIDGET(children->data), "active");
        children = children->next;
    }
    g_list_free(g_steal_pointer(&children));
}

// Function to set a chatlist item as active
void set_chatlist_item_active(GtkWidget *widget)
{
    GtkWidget *chatlist_container = gtk_widget_get_parent(widget);
    remove_active_class_from_chatlist_items(chatlist_container);
    add_class(widget, "active");
}
