#include "../inc/client.h"

// Function to build signup menu
void build_signup_menu()
{
    GtkWidget *main_area = get_widget_by_name_r(main_window, "main_area"); // Get the main area of the window to which the signup menu will be added

    // Create a vertical box for the signup menu
    GtkWidget *signup_menu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(main_area), signup_menu, false, false, 0);
    gtk_widget_set_name(signup_menu, "signup_menu");
    add_class(signup_menu, "signup_menu");

    // Title box
    GtkWidget *title_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    add_class(title_box, "auth-menu_title-block");
    GtkWidget *signup_menu_title = gtk_label_new("Create an account");
    gtk_widget_set_halign(signup_menu_title, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(signup_menu_title, GTK_ALIGN_CENTER);
    add_class(signup_menu_title, "auth-menu_title");

    gtk_box_pack_start(GTK_BOX(title_box), signup_menu_title, FALSE, FALSE, 0);

    // Username box
    GtkWidget *username_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    GtkWidget *username_field = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(username_field), "Username");
    gtk_widget_set_name(username_field, "username_field");
    add_class(username_field, "input-field");
    add_class(username_field, "input-field--name");
    g_signal_connect(G_OBJECT(username_field), "focus-out-event", G_CALLBACK(focus_out_username_field), NULL);

    GtkWidget *username_notify_label = gtk_label_new(" ");
    gtk_widget_set_halign(username_notify_label, GTK_ALIGN_START);
    gtk_widget_set_name(username_notify_label, "username_notify_label");
    add_class(username_notify_label, "notify-label");

    gtk_box_pack_start(GTK_BOX(username_box), username_field, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(username_box), username_notify_label, FALSE, FALSE, 0);

    // Password box
    GtkWidget *password_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    GtkWidget *password_field = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(password_field), "Password");
    gtk_widget_set_name(password_field, "password_field");
    add_class(password_field, "input-field");
    add_class(password_field, "input-field--password");
    gtk_entry_set_visibility(GTK_ENTRY(password_field), false);
    g_signal_connect(G_OBJECT(password_field), "focus-out-event", G_CALLBACK(focus_out_password_field), NULL);

    GtkWidget *password_notify_label = gtk_label_new(" ");
    gtk_widget_set_halign(password_notify_label, GTK_ALIGN_START);
    gtk_widget_set_name(password_notify_label, "password_notify_label");
    add_class(password_notify_label, "notify-label");

    gtk_box_pack_start(GTK_BOX(password_box), password_field, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(password_box), password_notify_label, FALSE, FALSE, 0);

    // Repassword box
    GtkWidget *repassword_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    GtkWidget *repassword_field = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(repassword_field), "Repeat password");
    gtk_widget_set_name(repassword_field, "repassword_field");
    add_class(repassword_field, "input-field");
    add_class(repassword_field, "input-field--password");
    gtk_entry_set_visibility(GTK_ENTRY(repassword_field), false);
    g_signal_connect(G_OBJECT(repassword_field), "focus-out-event", G_CALLBACK(focus_out_repassword_field), NULL);

    GtkWidget *repassword_notify_label = gtk_label_new(" ");
    gtk_widget_set_halign(repassword_notify_label, GTK_ALIGN_START);
    gtk_widget_set_name(repassword_notify_label, "repassword_notify_label");
    add_class(repassword_notify_label, "notify-label");

    gtk_box_pack_start(GTK_BOX(repassword_box), repassword_field, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(repassword_box), repassword_notify_label, FALSE, FALSE, 0);

    // Signup button box
    GtkWidget *signup_btn_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    GtkWidget *signup_btn = gtk_button_new_with_label("Sign up");
    g_signal_connect(G_OBJECT(signup_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(signup_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(signup_btn, "clicked", G_CALLBACK(signup_button_click), NULL);
    add_class(signup_btn, "btn");
    add_class(signup_btn, "btn--blue");

    GtkWidget *signup_notify_label = gtk_label_new(" ");
    gtk_widget_set_halign(signup_notify_label, GTK_ALIGN_CENTER);
    gtk_widget_set_name(signup_notify_label, "signup_notify_label");
    add_class(signup_notify_label, "notify-label");

    gtk_box_pack_start(GTK_BOX(signup_btn_box), signup_btn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(signup_btn_box), signup_notify_label, FALSE, FALSE, 0);

    // Event box for switching to login menu
    GtkWidget *event_switch_to_login = gtk_event_box_new();
    gtk_widget_set_halign(event_switch_to_login, GTK_ALIGN_START);
    add_class(event_switch_to_login, "event_switch_auth_menu");
    g_signal_connect(G_OBJECT(event_switch_to_login), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(event_switch_to_login), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(event_switch_to_login), "button_press_event", G_CALLBACK(switch_to_login_menu), NULL);

    GtkWidget *signup_label = gtk_label_new("Already have an account?");
    add_class(signup_label, "switch_auth_menu_label");
    gtk_container_add(GTK_CONTAINER(event_switch_to_login), signup_label);

    // Pack all components into the signup menu
    gtk_box_pack_start(GTK_BOX(signup_menu), title_box, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(signup_menu), username_box, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(signup_menu), password_box, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(signup_menu), repassword_box, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(signup_menu), signup_btn_box, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(signup_menu), event_switch_to_login, FALSE, FALSE, 0);

    gtk_widget_show_all(signup_menu); // Show all components of the signup menu
}
