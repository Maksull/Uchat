#include "../../inc/client.h"

// Helper function to create an event box for the edit button
static GtkWidget *create_edit_button(t_msg *message) {
    GtkWidget *edit_btn = gtk_event_box_new();
    gtk_widget_set_size_request(GTK_WIDGET(edit_btn), 20, 16);
    add_class(edit_btn, "edit_msg_btn");
    g_signal_connect(G_OBJECT(edit_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(edit_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
    g_signal_connect(G_OBJECT(edit_btn), "button_press_event", G_CALLBACK(edit_message), message);
    return edit_btn;
}

// Helper function to create a label for message text
static GtkWidget *create_message_text_label(const char *text, int cur_user) {
    GtkWidget *sent_message = gtk_label_new(text);
    gtk_widget_set_halign(GTK_WIDGET(sent_message), cur_user ? GTK_ALIGN_END : GTK_ALIGN_START);
    gtk_label_set_selectable(GTK_LABEL(sent_message), TRUE);
    gtk_label_set_single_line_mode(GTK_LABEL(sent_message), FALSE);
    gtk_label_set_max_width_chars(GTK_LABEL(sent_message), 50);
    gtk_label_set_line_wrap(GTK_LABEL(sent_message), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(sent_message), PANGO_WRAP_WORD);
    add_class(sent_message, cur_user ? "right_message" : "left_message");
    return sent_message;
}

// Helper function to create a label for message timestamp
static GtkWidget *create_message_time_label(const char *time, gboolean cur_user) {
    GtkWidget *message_time = gtk_label_new(time);
    add_class(message_time, "msg_time");
    gtk_widget_set_halign(GTK_WIDGET(message_time), cur_user ? GTK_ALIGN_END : GTK_ALIGN_START);
    return message_time;
}


// Add a message to the chat field
void add_message(t_msg *message)
{
    GtkWidget *chat_field = get_widget_by_name_r(main_window, "chat_field"); // Get chat field widget

    int cur_user = message->sender_id == utils->current_user->user_id ? 1 : 0; // Check if message is from current user

    GtkWidget *message_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);                        // Create horizontal box for message
    gtk_widget_set_halign(GTK_WIDGET(message_box), cur_user ? GTK_ALIGN_END : GTK_ALIGN_START); // Set message alignment
    gtk_widget_set_valign(GTK_WIDGET(message_box), cur_user ? GTK_ALIGN_END : GTK_ALIGN_START);
    gtk_widget_set_hexpand(message_box, TRUE); // Allow message box to expand horizontally
    add_class(message_box, "msg_box"); // Add CSS class to message box
    gtk_box_pack_start(GTK_BOX(chat_field), message_box, FALSE, FALSE, 0); // Pack message box into chat field

    GtkWidget *avatar = gtk_drawing_area_new(); // Create drawing area for avatar
    gtk_widget_set_size_request(GTK_WIDGET(avatar), 27, 27); // Set size of avatar
    g_signal_connect(G_OBJECT(avatar), "draw", G_CALLBACK(draw_user_avatar), (gpointer)message->avatar_color); // Connect draw signal for avatar
    gtk_widget_set_halign(avatar, cur_user ? GTK_ALIGN_START : GTK_ALIGN_END); // Set avatar alignment
    gtk_widget_set_valign(avatar, GTK_ALIGN_START);
    if (!cur_user)
    {
        gtk_box_pack_start(GTK_BOX(message_box), avatar, FALSE, FALSE, 0); // Pack avatar into message box if not current user
    }

    GtkWidget *message_text = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5); // Create vertical box for message text
    gtk_widget_set_halign(GTK_WIDGET(message_text), cur_user ? GTK_ALIGN_START : GTK_ALIGN_END); // Set message text alignment
    gtk_widget_set_valign(GTK_WIDGET(message_text), cur_user ? GTK_ALIGN_START : GTK_ALIGN_END);
    gtk_box_pack_start(GTK_BOX(message_box), message_text, false, false, 0); // Pack message text box into message box
    add_class(message_text, "msg_text"); // Add CSS class to message text box

    GtkWidget *message_head = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5); // Create horizontal box for message header
    gtk_box_pack_start(GTK_BOX(message_text), message_head, false, false, 0); // Pack message header into message text box
    add_class(message_head, "msg_head");                                      // Add CSS class to message header

    if (cur_user)
    {
        GtkWidget *delete_btn = gtk_event_box_new();                                                 // Create event box for delete button
        gtk_widget_set_size_request(GTK_WIDGET(delete_btn), 20, 16);                                 // Set size of delete button
        add_class(delete_btn, "delete_msg_btn");                                                     // Add CSS class to delete button
        g_signal_connect(G_OBJECT(delete_btn), "enter-notify-event", G_CALLBACK(on_crossing), NULL); // Connect signals for delete button
        g_signal_connect(G_OBJECT(delete_btn), "leave-notify-event", G_CALLBACK(on_crossing), NULL);
        g_signal_connect(G_OBJECT(delete_btn), "button_press_event", G_CALLBACK(delete_message), message);
        gtk_box_pack_start(GTK_BOX(message_head), delete_btn, FALSE, FALSE, 0); // Pack delete button into message header if current user
    }

    if (cur_user)
    {
        GtkWidget *edit_btn = create_edit_button(message);
        gtk_box_pack_start(GTK_BOX(message_head), edit_btn, FALSE, FALSE, 0); // Pack edit button into message header
    }

    GtkWidget *user_name = gtk_label_new(message->sender_name); // Create label for sender name
    add_class(user_name, "msg_name"); // Add CSS class to sender name label
    if (cur_user)
    {
        add_class(user_name, "msg_name--right"); // Add additional CSS class for sender name label if current user
        gtk_box_pack_end(GTK_BOX(message_head), user_name, false, false, 0); // Pack sender name label into message header if current user
    }
    else
    {
        add_class(user_name, "msg_name--left"); // Add additional CSS class for sender name label if not current user
        gtk_box_pack_start(GTK_BOX(message_head), user_name, false, false, 0); // Pack sender name label into message header if not current user
    }

    GtkWidget *sent_message = create_message_text_label(message->text, cur_user);
    gtk_box_pack_start(GTK_BOX(message_text), sent_message, false, false, 0); // Pack message text label into message text box

    GtkWidget *message_time = create_message_time_label(message->date_str, cur_user);
    gtk_box_pack_start(GTK_BOX(message_text), message_time, false, false, 0); // Pack message timestamp label into message text box

    if (cur_user)
    {
        gtk_box_pack_start(GTK_BOX(message_box), avatar, FALSE, FALSE, 0); // Pack avatar into message box if current user
    }

    gtk_widget_show_all(chat_field); // Show all widgets in chat field
}
