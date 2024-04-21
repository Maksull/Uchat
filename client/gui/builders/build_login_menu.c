#include "../../inc/client.h"

// Function definition to create the title box
static GtkWidget *create_title_box()
{
    GtkWidget *title_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    add_class(title_box, "auth-menu_title-block"); // Add class for styling

    GtkWidget *login_menu_title = gtk_label_new("Welcome back!"); // Create title label
    gtk_widget_set_halign(login_menu_title, GTK_ALIGN_CENTER);    // Set horizontal alignment
    gtk_widget_set_valign(login_menu_title, GTK_ALIGN_CENTER);    // Set vertical alignment
    add_class(login_menu_title, "auth-menu_title");               // Add class for styling

    GtkWidget *login_menu_subtitle = gtk_label_new("We're so excited to see you again!"); // Create subtitle label
    gtk_widget_set_halign(login_menu_subtitle, GTK_ALIGN_CENTER);                         // Set horizontal alignment
    gtk_widget_set_valign(login_menu_subtitle, GTK_ALIGN_CENTER);                         // Set vertical alignment
    add_class(login_menu_subtitle, "auth-menu_subtitle");                                 // Add class for styling

    gtk_box_pack_start(GTK_BOX(title_box), login_menu_title, FALSE, FALSE, 0);    // Pack title label into title box
    gtk_box_pack_start(GTK_BOX(title_box), login_menu_subtitle, FALSE, FALSE, 0); // Pack subtitle label into title box

    return title_box;
}

// Function definition to create the username box
static GtkWidget *create_username_box()
{
    GtkWidget *username_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    GtkWidget *username_field = gtk_entry_new();                           // Create username entry field
    gtk_entry_set_placeholder_text(GTK_ENTRY(username_field), "Username"); // Set placeholder text
    gtk_widget_set_name(username_field, "username_field");                 // Set name for styling
    add_class(username_field, "input-field");                              // Add class for styling
    add_class(username_field, "input-field--name");                        // Add class for styling

    GtkWidget *username_notify_label = gtk_label_new(" ");               // Create notification label for username
    gtk_widget_set_halign(username_notify_label, GTK_ALIGN_START);       // Set horizontal alignment
    gtk_widget_set_name(username_notify_label, "username_notify_label"); // Set name for styling
    add_class(username_notify_label, "notify-label");                    // Add class for styling

    gtk_box_pack_start(GTK_BOX(username_box), username_field, FALSE, FALSE, 0);        // Pack username field into username box
    gtk_box_pack_start(GTK_BOX(username_box), username_notify_label, FALSE, FALSE, 0); // Pack notification label into username box

    return username_box;
}

// Function definition to create the password box
static GtkWidget *create_password_box()
{
    GtkWidget *password_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    GtkWidget *password_field = gtk_entry_new();                           // Create password entry field
    gtk_entry_set_placeholder_text(GTK_ENTRY(password_field), "Password"); // Set placeholder text
    gtk_widget_set_name(password_field, "password_field");                 // Set name for styling
    add_class(password_field, "input-field");                              // Add class for styling
    add_class(password_field, "input-field--password");                    // Add class for styling
    gtk_entry_set_visibility(GTK_ENTRY(password_field), FALSE);            // Hide password characters

    GtkWidget *password_notify_label = gtk_label_new(" ");               // Create notification label for password
    gtk_widget_set_halign(password_notify_label, GTK_ALIGN_START);       // Set horizontal alignment
    gtk_widget_set_name(password_notify_label, "password_notify_label"); // Set name for styling
    add_class(password_notify_label, "notify-label");                    // Add class for styling

    gtk_box_pack_start(GTK_BOX(password_box), password_field, FALSE, FALSE, 0);        // Pack password field into password box
    gtk_box_pack_start(GTK_BOX(password_box), password_notify_label, FALSE, FALSE, 0); // Pack notification label into password box

    return password_box;
}

// Function definition to create the login button box
static GtkWidget *create_login_button_box()
{
    GtkWidget *login_btn_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    GtkWidget *login_btn = gtk_button_new_with_label("Login");                                  // Create login button
    g_signal_connect(G_OBJECT(login_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL); // Connect signal for mouse enter event
    g_signal_connect(G_OBJECT(login_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL); // Connect signal for mouse leave event
    g_signal_connect(login_btn, "clicked", G_CALLBACK(login_button_click), NULL);               // Connect signal for button click event
    add_class(login_btn, "btn");                                                                // Add class for styling
    add_class(login_btn, "btn--blue");                                                          // Add class for styling

    GtkWidget *login_notify_label = gtk_label_new(" ");            // Create notification label for login button
    gtk_widget_set_halign(login_notify_label, GTK_ALIGN_CENTER);   // Set horizontal alignment
    gtk_widget_set_name(login_notify_label, "login_notify_label"); // Set name for styling
    add_class(login_notify_label, "notify-label");                 // Add class for styling

    gtk_box_pack_start(GTK_BOX(login_btn_box), login_btn, FALSE, FALSE, 0);          // Pack login button into login button box
    gtk_box_pack_start(GTK_BOX(login_btn_box), login_notify_label, FALSE, FALSE, 0); // Pack notification label into login button box

    return login_btn_box;
}

// Function definition to create the text box
static GtkWidget *create_text_box()
{
    GtkWidget *text_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *label = gtk_label_new("Don't have an account yet? "); // Create label
    gtk_box_pack_start(GTK_BOX(text_box), label, FALSE, FALSE, 0);   // Pack label into text box
    return text_box;
}

// Function definition to create the signup event box
static GtkWidget *create_signup_event_box()
{
    GtkWidget *event_switch_to_signup = gtk_event_box_new();
    add_class(event_switch_to_signup, "event_switch_auth_menu");                                                       // Add class for styling
    g_signal_connect(G_OBJECT(event_switch_to_signup), "enter-notify-event", G_CALLBACK(on_crossing), NULL);           // Connect signal for mouse enter event
    g_signal_connect(G_OBJECT(event_switch_to_signup), "leave-notify-event", G_CALLBACK(on_crossing), NULL);           // Connect signal for mouse leave event
    g_signal_connect(G_OBJECT(event_switch_to_signup), "button_press_event", G_CALLBACK(switch_to_signup_menu), NULL); // Connect signal for button press event

    GtkWidget *signup_label = gtk_label_new("Register");                    // Create label
    add_class(signup_label, "switch_auth_menu_label");                      // Add class for styling
    gtk_container_add(GTK_CONTAINER(event_switch_to_signup), signup_label); // Add label to event box

    return event_switch_to_signup;
}

// Function to build the login menu
void build_login_menu()
{
    GtkWidget *main_area = get_widget_by_name_r(main_window, "main_area"); // Get the main_area widget from the main window

    GtkWidget *login_menu = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);   // Create a vertical box for login menu
    gtk_box_pack_start(GTK_BOX(main_area), login_menu, TRUE, FALSE, 0); // Pack login_menu into main_area
    gtk_widget_set_name(login_menu, "login_menu");                      // Set name for styling
    add_class(login_menu, "login_menu");                                // Add class for styling

    // Create the title box and pack it into login_menu
    GtkWidget *title_box = create_title_box();
    gtk_box_pack_start(GTK_BOX(login_menu), title_box, FALSE, FALSE, 0);

    // Create the username box and pack it into login_menu
    GtkWidget *username_box = create_username_box();
    gtk_box_pack_start(GTK_BOX(login_menu), username_box, FALSE, FALSE, 0);

    // Create the password box and pack it into login_menu
    GtkWidget *password_box = create_password_box();
    gtk_box_pack_start(GTK_BOX(login_menu), password_box, FALSE, FALSE, 0);

    // Create the login button box and pack it into login_menu
    GtkWidget *login_btn_box = create_login_button_box();
    gtk_box_pack_start(GTK_BOX(login_menu), login_btn_box, FALSE, FALSE, 0);

    // Create the text box and pack it into login_menu
    GtkWidget *text_box = create_text_box();
    gtk_box_pack_start(GTK_BOX(login_menu), text_box, FALSE, FALSE, 0);

    // Create the signup event box and pack it into text_box
    GtkWidget *signup_event_box = create_signup_event_box();
    gtk_box_pack_start(GTK_BOX(text_box), signup_event_box, FALSE, FALSE, 0);

    gtk_widget_show_all(login_menu); // Show all widgets in the login menu)
}
