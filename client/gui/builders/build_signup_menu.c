#include "../../inc/client.h"

// Helper function to create the title box
static GtkWidget *create_title_box() {
    GtkWidget *title_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    add_class(title_box, "auth-menu_title-block");

    GtkWidget *signup_menu_title = gtk_label_new("Create an account");
    gtk_widget_set_halign(signup_menu_title, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(signup_menu_title, GTK_ALIGN_CENTER);
    add_class(signup_menu_title, "auth-menu_title");

    gtk_box_pack_start(GTK_BOX(title_box), signup_menu_title, FALSE, FALSE, 0);

    return title_box;
}

// Helper function to create an input box with a placeholder text
static GtkWidget *create_input_box(const gchar *placeholder_text) {
    GtkWidget *input_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    GtkWidget *input_field = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(input_field), placeholder_text);
    gtk_widget_set_name(input_field, placeholder_text);
    add_class(input_field, "input-field");

    GtkWidget *notify_label = gtk_label_new(" ");
    gtk_widget_set_halign(notify_label, GTK_ALIGN_START);
    gtk_widget_set_name(notify_label, placeholder_text);
    add_class(notify_label, "notify-label");

    gtk_box_pack_start(GTK_BOX(input_box), input_field, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(input_box), notify_label, FALSE, FALSE, 0);

    return input_box;
}

// Helper function to create the signup button box
static GtkWidget *create_signup_btn_box() {
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

    return signup_btn_box;
}

// Helper function to create the event box for switching to login menu
static GtkWidget *create_switch_to_login_event_box() {
    GtkWidget *event_switch_to_login = gtk_event_box_new();
    gtk_widget_set_halign(event_switch_to_login, GTK_ALIGN_START);
    add_class(event_switch_to_login, "event_switch_auth_menu");
    g_signal_connect(G_OBJECT(event_switch_to_login), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(event_switch_to_login), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(event_switch_to_login), "button_press_event", G_CALLBACK(switch_to_login_menu), NULL);

    GtkWidget *signup_label = gtk_label_new("Already have an account?");
    add_class(signup_label, "switch_auth_menu_label");
    gtk_container_add(GTK_CONTAINER(event_switch_to_login), signup_label);

    return event_switch_to_login;
}

// Function to build signup menu
void build_signup_menu() {
    GtkWidget *main_area = get_widget_by_name_r(main_window, "main_area");
    clear_container(main_area);

    // Create a vertical box for the signup menu
    GtkWidget *signup_menu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(main_area), signup_menu, false, false, 0);
    gtk_widget_set_name(signup_menu, "signup_menu");
    add_class(signup_menu, "signup_menu");

    // Create a widgets for the signup menu
    GtkWidget *title_box = create_title_box();
    GtkWidget *username_box = create_input_box("Username");
    GtkWidget *password_box = create_input_box("Password");
    GtkWidget *repassword_box = create_input_box("Repeat password");
    GtkWidget *signup_btn_box = create_signup_btn_box();
    GtkWidget *event_switch_to_login = create_switch_to_login_event_box();

    // Packing widgets into vertical box
    gtk_box_pack_start(GTK_BOX(signup_menu), title_box, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(signup_menu), username_box, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(signup_menu), password_box, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(signup_menu), repassword_box, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(signup_menu), signup_btn_box, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(signup_menu), event_switch_to_login, FALSE, FALSE, 0);

    gtk_widget_show_all(signup_menu);
}
