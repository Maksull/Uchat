#include "../../inc/client.h"

// Function to build leftbar
void build_leftbar(GtkWidget *chat_screen)
{
    GtkWidget *left_bar = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); // Create a vertical box widget to serve as the left sidebar
    // Set size request and add CSS class for styling
    gtk_widget_set_size_request(GTK_WIDGET(left_bar), LEFT_BAR_W, WINDOW_HEIGHT);
    gtk_grid_attach(GTK_GRID(chat_screen), left_bar, 0, 0, 1, 1);
    add_class(left_bar, "leftbar");

    // Build and pack the header block into the left sidebar
    GtkWidget *header_block = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 2);
    add_class(header_block, "leftbar_header_block");

    GtkWidget *header_label = gtk_label_new("Messages");
    add_class(header_label, "leftbar_header_label");

    GtkWidget *create_new_chat_btn = gtk_event_box_new();
    add_class(create_new_chat_btn, "event_switch_auth_menu");
    g_signal_connect(G_OBJECT(create_new_chat_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(create_new_chat_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(create_new_chat_btn), "button_press_event", G_CALLBACK(popup_create_chat_menu), chat_screen);
    GtkWidget *create_chat_label = gtk_label_new("+ New chat");
    add_class(create_chat_label, "switch_auth_menu_label");
    gtk_container_add(GTK_CONTAINER(create_new_chat_btn), create_chat_label);

    gtk_box_pack_start(GTK_BOX(header_block), header_label, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(header_block), create_new_chat_btn, FALSE, FALSE, 0);

    // Build and pack the search block into the left sidebar
    GtkWidget *search_block = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 8);
    add_class(search_block, "search_block");

    GtkWidget *search_field = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(search_field), "Search");
    gtk_widget_set_name(search_field, "global_search_field");
    add_class(search_field, "input-field");
    add_class(search_field, "input-field--search");
    g_signal_connect(G_OBJECT(search_field), "changed", G_CALLBACK(search_field_change_event), NULL);

    GtkWidget *clear_field_btn = gtk_button_new();
    gtk_widget_set_size_request(GTK_WIDGET(clear_field_btn), 45, 45);
    add_class(clear_field_btn, "clear_search_btn");
    g_signal_connect(G_OBJECT(clear_field_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(clear_field_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(clear_field_btn), "clicked", G_CALLBACK(clear_search_field), search_field);

    gtk_box_pack_start(GTK_BOX(search_block), search_field, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(search_block), clear_field_btn, false, false, 0);

    // Build and pack the chat list into the left sidebar
    GtkWidget *scrollable_wrap = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_name(scrollable_wrap, "chatlist_scrollable_wrap");
    add_class(scrollable_wrap, "scrollable_wrap");

    GtkWidget *chatlist = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(chatlist, "chatlist");
    add_class(chatlist, "chatlist");
    gtk_container_add(GTK_CONTAINER(scrollable_wrap), chatlist);

    // Build and pack the user footer into the left sidebar
    GtkWidget *leftbar_footer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    add_class(leftbar_footer, "leftbar_footer");

    GtkWidget *user_avatar = gtk_drawing_area_new();
    gtk_widget_set_size_request(GTK_WIDGET(user_avatar), 27, 27);
    g_signal_connect(G_OBJECT(user_avatar), "draw", G_CALLBACK(draw_user_avatar), (gpointer)utils->current_user->avatar_color);
    gtk_widget_set_halign(user_avatar, GTK_ALIGN_START);
    gtk_widget_set_valign(user_avatar, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(leftbar_footer), user_avatar, FALSE, FALSE, 0);

    GtkWidget *username = gtk_label_new(utils->current_user->name);
    gtk_widget_set_name(username, "leftbar_footer_username");
    gtk_widget_set_halign(GTK_WIDGET(username), GTK_ALIGN_START);
    gtk_widget_set_valign(GTK_WIDGET(username), GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(leftbar_footer), username, false, false, 0);
    add_class(username, "leftbar_footer_username");

    GtkWidget *menubar = gtk_menu_bar_new();
    g_signal_connect(G_OBJECT(menubar), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(menubar), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    add_class(menubar, "menubar");
    GtkWidget *menu = gtk_menu_new();
    add_class(menu, "menubar_menu");
    GtkWidget *change_login_btn = gtk_menu_item_new_with_label("Change login");
    g_signal_connect(change_login_btn, "activate", G_CALLBACK(build_change_login_window), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), change_login_btn);
    GtkWidget *change_password_btn = gtk_menu_item_new_with_label("Change password");
    g_signal_connect(change_password_btn, "activate", G_CALLBACK(build_change_password_window), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), change_password_btn);
    GtkWidget *delete_account_btn = gtk_menu_item_new_with_label("Delete account");
    g_signal_connect(delete_account_btn, "activate", G_CALLBACK(build_confirm_delete_account_window), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), delete_account_btn);
    GtkWidget *logout_btn = gtk_menu_item_new_with_label("Log out");
    g_signal_connect(logout_btn, "activate", G_CALLBACK(build_confirm_logout_window), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), logout_btn);

    gtk_widget_set_halign(GTK_WIDGET(menubar), GTK_ALIGN_CENTER);
    gtk_widget_set_valign(GTK_WIDGET(menubar), GTK_ALIGN_START);
    gtk_box_pack_end(GTK_BOX(leftbar_footer), menubar, FALSE, FALSE, 0);

    GtkWidget *edit_profile_btn = gtk_menu_item_new_with_label("");
    gtk_widget_set_size_request(GTK_WIDGET(edit_profile_btn), 30, 30);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(edit_profile_btn), menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), edit_profile_btn);
    add_class(edit_profile_btn, "edit_profile_btn");

    // Pack the header block, search block, scrollable_wrap (chat list), and leftbar_footer into the left sidebar
    gtk_box_pack_start(GTK_BOX(left_bar), header_block, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(left_bar), search_block, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(left_bar), scrollable_wrap, true, true, 0);
    gtk_box_pack_start(GTK_BOX(left_bar), leftbar_footer, false, false, 0);
}
